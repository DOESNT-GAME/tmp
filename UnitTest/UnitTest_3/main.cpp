#include <QCoreApplication>
#include <QtTest>
#include "test_equation_solver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestEquationSolver test;
    return QTest::qExec(&test, argc, argv);
}
