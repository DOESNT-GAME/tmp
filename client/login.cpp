#include "login.h"
#include "ui_login.h"
#include "reg.h"
#include "singltoneclient.h"
#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    SingltoneClient::instance()->establishConnection();
    setWindowTitle("Login");
    ui->textEditStatus->setReadOnly(true);

    connect(SingltoneClient::instance(), &SingltoneClient::responseReceived, this, [this](const QString& text) {
        ui->textEditStatus->append("> Response:\n" + text);

        if (text.contains("Authentication successful", Qt::CaseInsensitive)) {
            if (!mainWindow)
                mainWindow = new MainWindow();
            mainWindow->show();
            this->hide();
        }
    });

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &LoginWindow::on_pushButtonRegister_clicked);
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginWindow::on_pushButtonLogin_clicked);

    QString lastResponse = SingltoneClient::instance()->latestResponse();
    if (!lastResponse.isEmpty()) {
        ui->textEditStatus->append("> Last response:\n" + lastResponse);
    }
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        ui->textEditStatus->append("Error: Fields cannot be empty");
        return;
    }

    QString command = QString("auth %1:%2").arg(username, password);
    SingltoneClient::instance()->transmitCommand(command);
}

void LoginWindow::on_pushButtonRegister_clicked() {
    RegisterDialog regDialog(this);
    regDialog.exec();
}
