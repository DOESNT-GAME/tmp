#include "authdialog.h"
#include "ui_authdialog.h"
#include "regdialog.h"
#include "singletonclient.h"
#include "mainwindow.h"

AuthDialog::AuthDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    SingletonClient::instance()->establishConnection();
    setWindowTitle("Login");
    ui->textEditStatus->setReadOnly(true);

    connect(SingletonClient::instance(), &SingletonClient::responseReceived, this, [this](const QString& text) {
        ui->textEditStatus->append("> Response:\n" + text);

        if (text.contains("Authentication successful", Qt::CaseInsensitive)) {
            if (!mainWindow)
                mainWindow = new MainWindow();
            mainWindow->show();
            this->hide();
        }
    });

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &AuthDialog::on_pushButtonRegister_clicked);
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &AuthDialog::on_pushButtonLogin_clicked);

    QString lastResponse = SingletonClient::instance()->latestResponse();
    if (!lastResponse.isEmpty()) {
        ui->textEditStatus->append("> Last response:\n" + lastResponse);
    }
}

AuthDialog::~AuthDialog() {
    delete ui;
}

void AuthDialog::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        ui->textEditStatus->append("Error: Fields cannot be empty");
        return;
    }

    QString command = QString("auth %1:%2").arg(username, password);
    SingletonClient::instance()->transmitCommand(command);
}

// void AuthDialog::on_pushButtonRegister_clicked() {
//     RegisterDialog regDialog(this);
//     regDialog.exec();
// }
