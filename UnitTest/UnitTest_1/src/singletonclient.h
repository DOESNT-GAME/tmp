#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include <QObject>
#include <QString>

class SingletonClient : public QObject
{
    Q_OBJECT
public:
    static SingletonClient* instance();
    static void setInstance(SingletonClient* instance);
    virtual void transmitCommand(const QString& command) = 0;

signals:
    void responseReceived(const QString& response);

protected:
    static SingletonClient* m_instance;
};

#endif // SINGLETONCLIENT_H
