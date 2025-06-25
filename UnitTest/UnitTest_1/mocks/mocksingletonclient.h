#ifndef MOCKSINGLETONCLIENT_H
#define MOCKSINGLETONCLIENT_H

#include "../src/singletonclient.h"

class MockSingletonClient : public SingletonClient
{
    Q_OBJECT
public:
    void transmitCommand(const QString& command) override
    {
        lastCommand = command;
        emit responseReceived("Mock response: " + command);
    }

    QString lastCommand;
};

#endif // MOCKSINGLETONCLIENT_H
