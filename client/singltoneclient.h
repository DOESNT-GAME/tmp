#pragma once

#include <QTcpSocket>
#include <QObject>

class SingltoneClient : public QObject {
    Q_OBJECT

signals:
    void responseReceived(const QString& message);

public:
    static SingltoneClient* instance();

    void establishConnection();
    void transmitCommand(const QString& command);
    QTcpSocket* socket() const;

    QString latestResponse() const;

private slots:
    void connectionEstablished();
    void dataAvailable();
    void connectionLost();

private:
    explicit SingltoneClient(QObject* parent = nullptr);

    QTcpSocket* m_socket;
    static SingltoneClient* m_instance;

    QString m_lastResponse;
};
