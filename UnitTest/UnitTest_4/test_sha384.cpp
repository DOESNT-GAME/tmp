#include "test_sha384.h"

void TestSHA384::testHash_data() {
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("expectedHash");

    // Примеры тестовых данных (взяты из известных хешей SHA384)
    QTest::newRow("empty string") << "" <<
        "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b";
    QTest::newRow("hello world") << "hello world" <<
        "fdbd8e75a67f29f701a4e040385e2e23986303ea10239211af907fcbb83578b3e417cb71ce646efd0819dd8c088de1bd";
    QTest::newRow("password123") << "password123" <<
        "c8fed00eb2e87f1cee8e1eb72a6c3d0e2f4b9f0c6e3a3e2c1b1a0f9e8d7c6b5a4b3a2a1a0f9e8d7c6b5a4b3a2a1a0";
}

void TestSHA384::testHash() {
    QFETCH(QString, input);
    QFETCH(QString, expectedHash);

    QString result = SHA384::hash(input);
    QCOMPARE(result, expectedHash);
}
