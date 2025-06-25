#include "test_registration.h"
#include <QSignalSpy>

TestRegistration::TestRegistration() {}
TestRegistration::~TestRegistration() {}

void TestRegistration::initTestCase()
{
    mockClient = new MockSingletonClient();
    SingletonClient::setInstance(mockClient);
    dialog = new RegisterDialog();
}

void TestRegistration::cleanupTestCase()
{
    delete dialog;
    delete mockClient;
}

void TestRegistration::testValidRegistration()
{
    dialog->usernameEdit()->setText("test_user");
    dialog->passwordEdit()->setText("password123");
    QTest::mouseClick(dialog->registerButton(), Qt::LeftButton);

    QCOMPARE(mockClient->lastCommand, QString("reg test_user:password123"));
}

void TestRegistration::testEmptyFields()
{
    dialog->usernameEdit()->setText("");
    dialog->passwordEdit()->setText("");
    QTest::mouseClick(dialog->registerButton(), Qt::LeftButton);

    QVERIFY(dialog->statusEdit()->toPlainText().contains("Please enter username and password"));
}

void TestRegistration::testServerResponse()
{
    QSignalSpy spy(mockClient, &MockSingletonClient::responseReceived);
    emit mockClient->responseReceived("Registration successful");

    QCOMPARE(spy.count(), 1);
    QCOMPARE(dialog->statusEdit()->toPlainText(), QString("Registration successful"));
}

int testRegistration(int argc, char *argv[])
{
    TestRegistration tc;
    return QTest::qExec(&tc, argc, argv);
}
