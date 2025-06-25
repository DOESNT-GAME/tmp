#pragma once

#include <QtWidgets/QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void onRegisterClicked();
    void onBackToLoginClicked();

private:
    Ui::RegisterDialog *ui;
signals:
    void showAuthRequested();
};
