#include "regdialog.h"
#include "ui_regdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonRegister, &QPushButton::clicked,
            this, &RegisterDialog::onRegisterClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

QLineEdit* RegisterDialog::usernameEdit() const { return ui->lineEditUsername; }
QLineEdit* RegisterDialog::passwordEdit() const { return ui->lineEditPassword; }
QTextEdit* RegisterDialog::statusEdit() const { return ui->textEditStatus; }
QPushButton* RegisterDialog::registerButton() const { return ui->pushButtonRegister; }

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
