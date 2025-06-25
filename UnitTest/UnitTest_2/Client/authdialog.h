#pragma once

#include <QtWidgets/QDialog>

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
    void on_pushButtonRegister_clicked();

private:
    Ui::AuthDialog *ui;

signals:
    void showRegisterRequested();
    void authSuccess();
};
