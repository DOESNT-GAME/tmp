#include "mytcpserver.h"
#include "dbmanager.h"
#include <QDebug>
#include <QJsonParseError>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server is not started";
    } else {
        qDebug() << "Server is started";
    }
}

MyTcpServer::~MyTcpServer() {
    mTcpServer->close();
}

void MyTcpServer::slotNewConnection() {
    while (mTcpServer->hasPendingConnections()) {
        QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
        clients.append(clientSocket);
        buffers[clientSocket] = QByteArray();

        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

        qDebug() << "Client connected:" << clientSocket->peerAddress().toString();
    }
}

void MyTcpServer::slotClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
        clients.removeAll(clientSocket);
        buffers.remove(clientSocket);
        clientSocket->deleteLater();
    }
}

void MyTcpServer::slotServerRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) return;

    buffers[clientSocket].append(clientSocket->readAll());

    // Здесь простой протокол — запрос заканчивается символом '\n'
    while (buffers[clientSocket].contains('\n')) {
        int index = buffers[clientSocket].indexOf('\n');
        QByteArray line = buffers[clientSocket].left(index);
        buffers[clientSocket].remove(0, index + 1);

        processRequest(clientSocket, line);
    }
}

void MyTcpServer::processRequest(QTcpSocket *socket, const QByteArray &requestData) {
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(requestData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        QJsonObject response;
        response["status"] = "error";
        response["message"] = "Invalid JSON";
        sendResponse(socket, response);
        return;
    }

    QJsonObject requestObj = doc.object();
    QString action = requestObj.value("action").toString();

    QJsonObject response;
    response["status"] = "ok";

    if (action == "login") {
        QString username = requestObj.value("username").toString();
        QString password = requestObj.value("password").toString();

        qDebug() << "Login request:" << username;
        // Проверка логина/пароля через единственный экземпляр DbManager
        if (DbManager::instance().validateUser(username, password)) {
            response["message"] = "Login successful";
        } else {
            response["status"] = "fail";
            response["message"] = "Invalid credentials";
        }

    } else if (action == "register") {
        QString username = requestObj.value("username").toString();
        QString password = requestObj.value("password").toString();

        qDebug() << "Register request:" << username;
        // Проверка логина/пароля через единственный экземпляр DbManager
        if (DbManager::instance().addUser(username, password)) {
            response["message"] = "Registration successful";
        } else {
            response["status"] = "fail";
            response["message"] = "Username already exists";
        }

    } else {
        response["status"] = "fail";
        response["message"] = "Unknown action";
    }

    sendResponse(socket, response);
}

void MyTcpServer::sendResponse(QTcpSocket *socket, const QJsonObject &response) {
    QJsonDocument doc(response);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    data.append('\n'); // Добавляем разделитель

    socket->write(data);
    socket->flush();
}
