#ifndef TEST_SHA384_H
#define TEST_SHA384_H

#include <QtTest/QtTest>
#include "sha384.h"

class TestSHA384 : public QObject {
    Q_OBJECT

private slots:
    void testHash_data();
    void testHash();
};

#endif // TEST_SHA384_H
