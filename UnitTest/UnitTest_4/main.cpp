#include <QApplication>
#include <QtTest>
#include "test_sha384.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv); // Теперь компилятор видит полное определение QApplication

    TestSHA384 testSHA384;
    return QTest::qExec(&testSHA384, argc, argv);
}
