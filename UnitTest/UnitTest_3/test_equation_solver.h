#pragma once

#include <QtTest/QtTest>
#include "equation_solver.h"

class TestEquationSolver : public QObject
{
    Q_OBJECT
private slots:
    void testChordMethod_data();
    void testChordMethod();

private:
    EquationSolver solver;
};
