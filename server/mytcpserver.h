#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

/**
 * @brief TCP server for handling client connections and commands
 */
class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject* parent = nullptr);
    ~TcpServer();

private slots:
    void handleNewConnection();
    void handleClientDisconnected(QTcpSocket* socket);
    void processClientData(QTcpSocket* socket);

private:
    void processRegistration(QTcpSocket* socket, const QString& credentials);
    void processAuthentication(QTcpSocket* socket, const QString& credentials);
    void processEquation(QTcpSocket* socket, const QString& arguments);
    void processEncryption(QTcpSocket* socket, const QString& text);
    void processSolution(QTcpSocket* socket, const QString& arguments);
    void sendResponse(QTcpSocket* socket, const QString& message);

    QTcpServer* m_server;
    QList<QTcpSocket*> m_connectedClients;
};

#endif // MYTCPSERVER_H
