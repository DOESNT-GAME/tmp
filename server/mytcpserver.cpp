#include "mytcpserver.h"
#include "dbmanager.h"
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>

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
    // Получаем все данные и разбиваем по строкам
    QString data = QString::fromUtf8(socket->readAll());
    QStringList commands = data.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);

    for (const QString& rawCommand : commands) {
        QString command = rawCommand.trimmed();
        if (command.isEmpty()) continue;

        qDebug() << "Processing command:" << command;

        // Разбиваем команду на части
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

    QSqlQuery query(DatabaseManager::instance()->database());
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        sendResponse(socket, "Error: User already exists");
        return;
    }

    query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

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

        // Дополнительная проверка - выведем всех пользователей в БД
        QSqlQuery allUsers(DatabaseManager::instance()->database());
        if (allUsers.exec("SELECT login FROM users")) {
            qDebug() << "Existing users in DB:";
            while (allUsers.next()) {
                qDebug() << "-" << allUsers.value(0).toString();
            }
        }
        return;
    }

    QString dbPassword = query.value(0).toString();
    if (dbPassword == password) {
        sendResponse(socket, "Authentication successful");
        qInfo() << "User authenticated:" << login;
    } else {
        sendResponse(socket, "Error: Invalid password");
        qDebug() << "Password mismatch for user:" << login;
    }
}

void TcpServer::sendResponse(QTcpSocket* socket, const QString& message)
{
    socket->write(message.toUtf8() + "\r\n");
}
