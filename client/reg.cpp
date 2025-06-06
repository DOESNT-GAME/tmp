#include "reg.h"
#include "ui_reg.h"
#include "singltoneclient.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle("Registration");
    ui->textEditStatus->setReadOnly(true);

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &RegisterDialog::onRegisterClicked);

    connect(SingltoneClient::instance(), &SingltoneClient::responseReceived, this, [this](const QString& response) {
        ui->textEditStatus->setText(response);

        if (response.contains("Registration successful", Qt::CaseInsensitive)) {
            this->accept();
        }
    });
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
    SingltoneClient::instance()->transmitCommand(command);
}
