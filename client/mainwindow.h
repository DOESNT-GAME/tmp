#pragma once

#include <QtWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonProcess_clicked();
    void on_pushButtonLoadImage_clicked();
    void on_pushButtonSolveEquation_clicked();
    void on_pushButtonLogout_clicked();

private:
    Ui::MainWindow *ui;
    QString currentImagePath;
    double chordMethod(double a, double b, double epsilon);
};
