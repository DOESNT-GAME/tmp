#include "singletonclient.h"
#include <QDebug>

SingletonClient* SingletonClient::m_instance = nullptr;

SingletonClient::SingletonClient(QObject* parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &SingletonClient::connectionEstablished);
    connect(m_socket, &QTcpSocket::readyRead, this, &SingletonClient::dataAvailable);
    connect(m_socket, &QTcpSocket::disconnected, this, &SingletonClient::connectionLost);
}

SingletonClient* SingletonClient::instance() {
    if (!m_instance) {
        m_instance = new SingletonClient();
    }
    return m_instance;
}

void SingletonClient::establishConnection() {
    qDebug() << "Establishing server connection...";
    m_socket->connectToHost("127.0.0.1", 33333);
}

void SingletonClient::transmitCommand(const QString& command)
{
    if (socket()->state() == QAbstractSocket::ConnectedState) {
        QString formattedCmd = command.trimmed() + "\r\n";
        socket()->write(formattedCmd.toUtf8());
        qDebug() << "Command sent:" << formattedCmd.trimmed();
    }
}

void SingletonClient::connectionEstablished() {
    qDebug() << "Server connection established";
}

void SingletonClient::dataAvailable() {
    QByteArray response = m_socket->readAll();
    QString text = QString::fromUtf8(response).trimmed().replace("\r", "");

    m_lastResponse = text;
    emit responseReceived(text);
}

void SingletonClient::connectionLost() {
    qDebug() << "Disconnected from server";
}

QTcpSocket* SingletonClient::socket() const {
    return m_socket;
}

QString SingletonClient::latestResponse() const {
    return m_lastResponse;
}
