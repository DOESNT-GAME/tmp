#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "singletonclient.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

    QLineEdit* usernameEdit() const;
    QLineEdit* passwordEdit() const;
    QTextEdit* statusEdit() const;
    QPushButton* registerButton() const;

protected slots:
    void onRegisterClicked();

private:
    Ui::RegisterDialog *ui;
};
