#include "equation_solver.h"
#include <cmath>
#include <QDebug>

EquationSolver::EquationSolver(QObject *parent) : QObject(parent) {}

double EquationSolver::solveByChordMethod(const QString& function, double a, double b, double epsilon)
{
    // Здесь должна быть реализация метода хорд
    // Это примерная заглушка - замените на реальную реализацию
    auto f = [](double x) { return x*x - 2; }; // Пример функции

    double fa = f(a);
    double fb = f(b);

    if (fa * fb >= 0) {
        qWarning() << "Function has same signs at a and b";
        return NAN;
    }

    double c = a;
    while ((b - a) >= epsilon) {
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        if (f(c) == 0.0) break;
        else if (f(c) * f(a) < 0) b = c;
        else a = c;
    }
    return c;
}
