#include "test_auth.h"
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Для тестов, использующих Qt GUI

    TestAuth testAuth;
    return QTest::qExec(&testAuth, argc, argv);
}
