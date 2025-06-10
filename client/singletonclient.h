#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtCore/QObject>

class SingletonClient : public QObject {
    Q_OBJECT

signals:
    void responseReceived(const QString& message);

public:
    static SingletonClient* instance();

    void establishConnection();
    void transmitCommand(const QString& command);
    QTcpSocket* socket() const;

    QString latestResponse() const;

private slots:
    void connectionEstablished();
    void dataAvailable();
    void connectionLost();

private:
    explicit SingletonClient(QObject* parent = nullptr);

    QTcpSocket* m_socket;
    static SingletonClient* m_instance;

    QString m_lastResponse;
};
