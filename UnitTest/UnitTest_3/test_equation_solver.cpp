#include "test_equation_solver.h"

void TestEquationSolver::testChordMethod_data()
{
    QTest::addColumn<QString>("function");
    QTest::addColumn<double>("a");
    QTest::addColumn<double>("b");
    QTest::addColumn<double>("epsilon");
    QTest::addColumn<double>("expected");

    // Тестовые данные
    QTest::newRow("x^2 - 2") << "x^2 - 2" << 1.0 << 2.0 << 0.0001 << sqrt(2);
    QTest::newRow("sin(x)") << "sin(x)" << 3.0 << 4.0 << 0.0001 << M_PI;
}

void TestEquationSolver::testChordMethod()
{
    QFETCH(QString, function);
    QFETCH(double, a);
    QFETCH(double, b);
    QFETCH(double, epsilon);
    QFETCH(double, expected);

    double result = solver.solveByChordMethod(function, a, b, epsilon);
    QVERIFY2(!std::isnan(result), "Solution not found");
    QVERIFY2(fabs(result - expected) < epsilon, "Result not within expected precision");
}
