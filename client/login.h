#pragma once

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked();

private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow = nullptr;
};
