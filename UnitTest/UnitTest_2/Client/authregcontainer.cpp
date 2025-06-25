#include "authregcontainer.h"
#include <QtWidgets/QBoxLayout>

AuthRegContainer::AuthRegContainer(QWidget *parent) : QWidget(parent) {
    stackedWidget = new QStackedWidget(this);

    authDialog = new AuthDialog();
    regDialog = new RegisterDialog();

    stackedWidget->addWidget(authDialog);
    stackedWidget->addWidget(regDialog);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    setLayout(layout);

    // Подключение сигналов для переключения окон
    connect(authDialog, &AuthDialog::showRegisterRequested, this, [this]() {
        stackedWidget->setCurrentWidget(regDialog);
    });

    connect(regDialog, &RegisterDialog::showAuthRequested, this, [this]() {
        stackedWidget->setCurrentWidget(authDialog);
    });
}
