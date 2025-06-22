#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singletonclient.h"
#include "authdialog.h"
#include <QFileDialog>
#include <cmath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Crypto Application");
    ui->textEdit->setReadOnly(true);

    QString lastResponse = SingletonClient::instance()->latestResponse();
    if (!lastResponse.isEmpty()) {
        ui->textEdit->append("> Last response:\n" + lastResponse);
    }

    connect(ui->pushButtonProcess, &QPushButton::clicked, this, &MainWindow::on_pushButtonProcess_clicked);
    connect(ui->pushButtonLoadImage, &QPushButton::clicked, this, &MainWindow::on_pushButtonLoadImage_clicked);
    connect(ui->pushButtonSolveEquation, &QPushButton::clicked, this, &MainWindow::on_pushButtonSolveEquation_clicked);
    connect(ui->pushButtonLogout, &QPushButton::clicked, this, &MainWindow::on_pushButtonLogout_clicked);

    connect(SingletonClient::instance(), &SingletonClient::responseReceived, this, [this](const QString& text) {
        if (text.contains("Error:")) {
            ui->textEdit->append("> Error: " + text);
        } else {
            ui->textEdit->append("> Server response:\n" + text);
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonProcess_clicked()
{
    QString input = ui->lineEditInput->text().trimmed();
    if (input.isEmpty()) {
        ui->textEdit->append("> Error: Input is empty");
        return;
    }

    ui->textEdit->append("> Processing encryption request: " + input);
    SingletonClient::instance()->transmitCommand("ENCRYPT:" + input);
}

void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        currentImagePath = filePath;
        ui->textEdit->append("> Image loaded: " + filePath);
    }
}

void MainWindow::on_pushButtonSolveEquation_clicked()
{
    QString func = ui->funcInput->text().trimmed();
    double a = ui->doubleSpinBoxA->value();
    double b = ui->doubleSpinBoxB->value();
    double epsilon = ui->doubleSpinBoxEpsilon->value();

    if (a >= b) {
        QMessageBox::warning(this, "Error", "Value 'a' must be less than 'b'");
        return;
    }

    // Формируем команду в правильном формате (нижний регистр + пробел)
    QString equationCmd = QString("equation: %1:%2:%3:%4")
                              .arg(func)
                              .arg(a)
                              .arg(b)
                              .arg(epsilon);

    ui->textEdit->append("> Sending equation to server: " + equationCmd);
    SingletonClient::instance()->transmitCommand(equationCmd);
}

void MainWindow::on_pushButtonLogout_clicked()
{
    AuthDialog *authDialog = new AuthDialog();
    authDialog->show();
    this->close();
}
