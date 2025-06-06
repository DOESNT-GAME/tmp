#include "singltoneclient.h"
#include <QDebug>

SingltoneClient* SingltoneClient::m_instance = nullptr;

SingltoneClient::SingltoneClient(QObject* parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &SingltoneClient::connectionEstablished);
    connect(m_socket, &QTcpSocket::readyRead, this, &SingltoneClient::dataAvailable);
    connect(m_socket, &QTcpSocket::disconnected, this, &SingltoneClient::connectionLost);
}

SingltoneClient* SingltoneClient::instance() {
    if (!m_instance) {
        m_instance = new SingltoneClient();
    }
    return m_instance;
}

void SingltoneClient::establishConnection() {
    qDebug() << "Establishing server connection...";
    m_socket->connectToHost("127.0.0.1", 33333);
}

void SingltoneClient::transmitCommand(const QString& command)
{
    if (socket()->state() == QAbstractSocket::ConnectedState) {
        QString formattedCmd = command.trimmed() + "\r\n";
        socket()->write(formattedCmd.toUtf8());
        qDebug() << "Command sent:" << formattedCmd.trimmed();
    }
}

void SingltoneClient::connectionEstablished() {
    qDebug() << "Server connection established";
}

void SingltoneClient::dataAvailable() {
    QByteArray response = m_socket->readAll();
    QString text = QString::fromUtf8(response).trimmed().replace("\r", "");

    m_lastResponse = text;
    emit responseReceived(text);
}

void SingltoneClient::connectionLost() {
    qDebug() << "Disconnected from server";
}

QTcpSocket* SingltoneClient::socket() const {
    return m_socket;
}

QString SingltoneClient::latestResponse() const {
    return m_lastResponse;
}
