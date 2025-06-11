#include "regdialog.h"
#include "ui_regdialog.h"
#include "singletonclient.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle("Registration");
    ui->textEditStatus->setReadOnly(true);

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &RegisterDialog::onRegisterClicked);
    connect(ui->pushButtonBackToLogin, &QPushButton::clicked, this, &RegisterDialog::onBackToLoginClicked);

    connect(SingletonClient::instance(), &SingletonClient::responseReceived, this, [this](const QString& response) {
        ui->textEditStatus->setText(response);

        if (response.contains("Registration successful", Qt::CaseInsensitive)) {
            emit showAuthRequested();
        }
    });
}

void RegisterDialog::onBackToLoginClicked() {
    emit showAuthRequested();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onRegisterClicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        ui->textEditStatus->setText("Please enter username and password.");
        return;
    }

    QString command = QString("reg %1:%2").arg(username, password);
    SingletonClient::instance()->transmitCommand(command);
}
