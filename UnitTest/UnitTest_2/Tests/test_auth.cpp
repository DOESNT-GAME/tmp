#include "test_auth.h"
#include <QTest>
#include <QSignalSpy>

void TestAuth::initTestCase()
{
    // Запускаем сервер на тестовом порту
    server = new TcpServer();

    // Настраиваем клиент
    client = SingletonClient::instance();
    client->socket()->connectToHost("127.0.0.1", 33333);
    QVERIFY(client->socket()->waitForConnected(1000));
}

void TestAuth::cleanupTestCase()
{
    client->socket()->disconnectFromHost();
    delete server;
}

void TestAuth::testRegistration()
{
    // Отправляем команду регистрации
    client->transmitCommand("reg testuser:testpass");

    // Ждем ответа
    QSignalSpy spy(client, &SingletonClient::responseReceived);
    QVERIFY(spy.wait(1000));

    // Проверяем, что регистрация прошла успешно
    QString response = spy.takeFirst().at(0).toString();
    QVERIFY(response.contains("Registration successful"));
}

void TestAuth::testAuthSuccess()
{
    client->transmitCommand("reg testuser:testpass");
    QSignalSpy spyReg(client, &SingletonClient::responseReceived);
    spyReg.wait(1000);

    // Тестируем аутентификацию
    client->transmitCommand("auth testuser:testpass");

    QSignalSpy spyAuth(client, &SingletonClient::responseReceived);
    QVERIFY(spyAuth.wait(1000));

    QString response = spyAuth.takeFirst().at(0).toString();
    QVERIFY(response.contains("Authentication successful"));
}

void TestAuth::testAuthFailure()
{
    // Неправильный пароль
    client->transmitCommand("auth testuser:wrongpassword");

    QSignalSpy spy(client, &SingletonClient::responseReceived);
    QVERIFY(spy.wait(1000));

    QString response = spy.takeFirst().at(0).toString();
    QVERIFY(response.contains("Error: Invalid password"));
}
