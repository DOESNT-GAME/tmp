#ifndef TEST_REGISTRATION_H
#define TEST_REGISTRATION_H

#include <QtTest>
#include "../src/regdialog.h"
#include "../mocks/mocksingletonclient.h"

class TestRegistration : public QObject
{
    Q_OBJECT

public:
    TestRegistration();
    ~TestRegistration();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void testValidRegistration();
    void testEmptyFields();
    void testServerResponse();

private:
    RegisterDialog* dialog;
    MockSingletonClient* mockClient;
};

// ќбъ€вл€ем функцию дл€ запуска тестов
int testRegistration(int argc, char* argv[]);

#endif // TEST_REGISTRATION_H