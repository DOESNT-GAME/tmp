#pragma once

#include <QObject>
#include <QString>

class EquationSolver : public QObject
{
    Q_OBJECT
public:
    explicit EquationSolver(QObject *parent = nullptr);
    double solveByChordMethod(const QString& function, double a, double b, double epsilon);
};
