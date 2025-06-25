#ifndef TEST_AUTH_H
#define TEST_AUTH_H

#include <QObject>
#include <QtTest/QtTest>
#include "../Client/singletonclient.h"
#include "../Server/mytcpserver.h"

class TestAuth : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();      // Выполняется перед всеми тестами
    void cleanupTestCase();   // Выполняется после всех тестов
    void testRegistration();  // Тест регистрации
    void testAuthSuccess();   // Тест успешной авторизации
    void testAuthFailure();   // Тест неудачной авторизации

private:
    TcpServer* server;
    SingletonClient* client;
};

#endif // TEST_AUTH_H
