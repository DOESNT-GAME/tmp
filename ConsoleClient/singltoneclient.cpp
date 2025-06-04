#include "singltoneclient.h"

SingltoneClient* SingltoneClient::p_instance = nullptr;
SingltoneClientDestroyer SingltoneClient::destroyer;

SingltoneClient::SingltoneClient(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
}

SingltoneClient* SingltoneClient::getInstance()
{
    if (!p_instance)
    {
        p_instance = new SingltoneClient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}
void SingltoneClient::sendMsgToServer(const QString& msg)
{
    mTcpSocket->write(msg.toUtf8());
}

void SingltoneClient::slotServerRead()
{
    QString msg = "";

    while (mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }

    qDebug() << msg;
    emit msgFromServer(msg);
}
