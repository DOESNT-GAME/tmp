#include "mytcpserver.h"
#include "dbmanager.h"
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QString>
#include <cmath>
#include <QJSEngine>
#include <QJSValue>

TcpServer::TcpServer(QObject* parent) : QObject(parent),
    m_server(new QTcpServer(this))
{
    if (!m_server->listen(QHostAddress::Any, 33333)) {
        qCritical() << "Failed to start server";
    } else {
        qInfo() << "Server started on port 33333";
        connect(m_server, &QTcpServer::newConnection,
                this, &TcpServer::handleNewConnection);
    }
}

TcpServer::~TcpServer()
{
    m_server->close();
    qDeleteAll(m_connectedClients);
}

void TcpServer::handleNewConnection()
{
    QTcpSocket* clientSocket = m_server->nextPendingConnection();
    m_connectedClients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead,
            this, [this, clientSocket]() { processClientData(clientSocket); });
    connect(clientSocket, &QTcpSocket::disconnected,
            this, [this, clientSocket]() { handleClientDisconnected(clientSocket); });

    sendResponse(clientSocket, "Connected to server");
}

void TcpServer::handleClientDisconnected(QTcpSocket* socket)
{
    m_connectedClients.removeAll(socket);
    socket->deleteLater();
    qInfo() << "Client disconnected";
}

void TcpServer::processClientData(QTcpSocket* socket)
{
    QString data = QString::fromUtf8(socket->readAll());
    QStringList commands = data.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);

    for (const QString& rawCommand : commands) {
        QString command = rawCommand.trimmed();
        if (command.isEmpty()) continue;

        qDebug() << "Processing command:" << command;

        QStringList parts = command.split(" ", Qt::SkipEmptyParts);
        if (parts.isEmpty()) {
            sendResponse(socket, "Error: Empty command");
            continue;
        }

        QString cmd = parts[0].toLower();
        QString args = parts.size() > 1 ? parts.mid(1).join(" ") : "";

        if (cmd == "reg") {
            processRegistration(socket, args);
        }
        else if (cmd == "auth") {
            processAuthentication(socket, args);
        }
        else if (command.startsWith("equation:", Qt::CaseInsensitive)) {
            QString args = command.mid(9).trimmed(); // Берем всё после "equation:"
            processEquation(socket, args);
        }
        else if (cmd == "encrypt:") {
            processEncryption(socket, args);
        }
        else if (cmd == "decrypt:") {
            processDecryption(socket, args);
        }
        else {
            sendResponse(socket, "Error: Unknown command");
        }
    }
}

void TcpServer::processRegistration(QTcpSocket* socket, const QString& credentials)
{
    const QStringList parts = credentials.split(":");
    if (parts.size() != 2) {
        sendResponse(socket, "Error: Use format 'reg login:password'");
        return;
    }

    const QString login = parts[0].trimmed();
    const QString password = parts[1].trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        sendResponse(socket, "Error: Login and password cannot be empty");
        return;
    }

    QString hashedPassword = DatabaseManager::hashPassword(password);

    QSqlQuery query(DatabaseManager::instance()->database());
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        sendResponse(socket, "Error: User already exists");
        return;
    }

    query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", hashedPassword);

    if (query.exec()) {
        sendResponse(socket, "Registration successful");
    } else {
        sendResponse(socket, "Error: Registration failed");
        qWarning() << "Database error:" << query.lastError().text();
    }
}

void TcpServer::processAuthentication(QTcpSocket* socket, const QString& arguments)
{
    qDebug() << "Auth arguments:" << arguments;

    QStringList creds = arguments.split(":", Qt::SkipEmptyParts);
    if (creds.size() != 2) {
        sendResponse(socket, "Error: Use format 'auth login:password'");
        qDebug() << "Invalid auth format, received:" << arguments;
        return;
    }

    QString login = creds[0].trimmed();
    QString password = creds[1].trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        sendResponse(socket, "Error: Login and password cannot be empty");
        return;
    }

    QString hashedPassword = DatabaseManager::hashPassword(password);

    qDebug() << "Attempting auth for user:" << login;

    QSqlQuery query(DatabaseManager::instance()->database());
    query.prepare("SELECT password FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        sendResponse(socket, "Error: Database error");
        qCritical() << "Database error:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        sendResponse(socket, "Error: User not found");
        qDebug() << "User not found in database:" << login;
        return;
    }

    QString dbPassword = query.value(0).toString();
    if (dbPassword == hashedPassword) {
        sendResponse(socket, "Authentication successful");
        qInfo() << "User authenticated:" << login;
    } else {
        sendResponse(socket, "Error: Invalid password");
        qDebug() << "Password mismatch for user:" << login;
    }
}

void TcpServer::processEquation(QTcpSocket* socket, const QString& arguments)
{
    qDebug() << "Equation arguments:" << arguments;

    QStringList parts = arguments.split(":");
    if (parts.size() != 4) {
        sendResponse(socket, "Error: Invalid equation format. Use 'equation: f(x):a:b:epsilon'");
        return;
    }

    QString funcStr = parts[0].trimmed();
    double a = parts[1].toDouble();
    double b = parts[2].toDouble();
    double epsilon = parts[3].toDouble();

    if (a >= b) {
        sendResponse(socket, "Error: 'a' must be less than 'b'");
        return;
    }

    // Функция для вычисления значения выражения
    auto evaluate = [funcStr](double x) -> double {
        QString expr = funcStr;
        expr.replace("x", QString::number(x));
        expr.replace("^", "**"); // Заменяем ^ на ** для совместимости

        QJSEngine engine;
        QJSValue result = engine.evaluate(expr);
        if (result.isError()) {
            throw std::runtime_error("Invalid function expression");
        }
        return result.toNumber();
    };

    // Проверяем функцию в точках a и b
    double fa, fb;
    try {
        fa = evaluate(a);
        fb = evaluate(b);
    } catch (const std::exception& e) {
        sendResponse(socket, QString("Error: Invalid function expression - %1").arg(e.what()));
        return;
    }

    if (fa * fb > 0) {
        sendResponse(socket, "Error: Function must have different signs at a and b");
        return;
    }

    int iterations = 0;
    double x = 0;
    const int maxIterations = 1000;

    do {
        x = a - fa * (b - a) / (fb - fa);
        double fx = evaluate(x);

        if (fx * fa < 0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }
        iterations++;
    } while (fabs(b - a) > epsilon && iterations < maxIterations);

    QString response = QString("Solution found:\n"
                               "x ≈ %1\n"
                               "Iterations: %2\n"
                               "Function: %3\n"
                               "Interval: [%4, %5]\n"
                               "Precision: %6")
                           .arg(x, 0, 'f', 6)
                           .arg(iterations)
                           .arg(funcStr)
                           .arg(parts[1])
                           .arg(parts[2])
                           .arg(epsilon);

    sendResponse(socket, response);
}

void TcpServer::processEncryption(QTcpSocket* socket, const QString& text)
{
    qDebug() << "Encryption request received:" << text;

    sendResponse(socket, "Text encrypted successfully (stub implementation)");
    qInfo() << "Text encrypted for client:" << socket->peerAddress().toString();
}

void TcpServer::processDecryption(QTcpSocket* socket, const QString& text)
{
    qDebug() << "Decryption request received:" << text;
    sendResponse(socket, "Decryption processed (stub implementation)");
    qInfo() << "Decryption processed for client:" << socket->peerAddress().toString();
}

void TcpServer::sendResponse(QTcpSocket* socket, const QString& message)
{
    socket->write(message.toUtf8() + "\r\n");
}
