#pragma once

#include <QtWidgets/QWidget>
#include <QStackedWidget>
#include "authdialog.h"
#include "regdialog.h"

class AuthRegContainer : public QWidget {
    Q_OBJECT

public:
    explicit AuthRegContainer(QWidget *parent = nullptr);

private:
    QStackedWidget *stackedWidget;
    AuthDialog *authDialog;
    RegisterDialog *regDialog;
};
