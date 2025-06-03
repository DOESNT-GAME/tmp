#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class MyTcpServer : public QObject {
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();

private:
    QTcpServer *mTcpServer;
    QList<QTcpSocket*> clients;  // Для нескольких клиентов
    QMap<QTcpSocket*, QByteArray> buffers;  // Буферы для каждого клиента

    void processRequest(QTcpSocket *socket, const QByteArray &requestData);
    void sendResponse(QTcpSocket *socket, const QJsonObject &response);
};

#endif // MYTCPSERVER_H
