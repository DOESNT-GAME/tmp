#ifndef SINGLTONECLIENT_H
#define SINGLTONECLIENT_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>

class SingltoneClient;

class SingltoneClientDestroyer {
private:
    SingltoneClient* p_instance;
public:
    ~SingltoneClientDestroyer() { delete p_instance; }
    void initialize(SingltoneClient* p) { p_instance = p; }
};

class SingltoneClient : public QObject {
    Q_OBJECT

private:
    static SingltoneClient* p_instance;
    static SingltoneClientDestroyer destroyer;
    QTcpSocket* mTcpSocket;

    // Закрытые конструкторы
    explicit SingltoneClient(QObject* parent = nullptr);
    SingltoneClient(const SingltoneClient&) = delete;
    SingltoneClient& operator=(const SingltoneClient&) = delete;
    friend class SingltoneClientDestroyer;

private slots:
    void slotServerRead();

public:
    static SingltoneClient* getInstance();
    void sendMsgToServer(const QString& msg);

signals:
    void msgFromServer(const QString& msg);
};

#endif // SINGLTONECLIENT_H
