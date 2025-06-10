#pragma once

#include <QtWidgets/QDialog>
#include "mainwindow.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    ~AuthDialog();

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked() { emit showRegisterRequested(); }

private:
    Ui::AuthDialog *ui;
    MainWindow *mainWindow = nullptr;
signals:
    void showRegisterRequested();
};
