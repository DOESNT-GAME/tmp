#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singltoneclient.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Crypto Application");
    ui->textEdit->setReadOnly(true);

    QString lastResponse = SingltoneClient::instance()->latestResponse();
    if (!lastResponse.isEmpty()) {
        ui->textEdit->append("> Last response:\n" + lastResponse);
    }

    connect(ui->pushButtonProcess, &QPushButton::clicked, this, &MainWindow::on_pushButtonProcess_clicked);
    connect(ui->pushButtonLoadImage, &QPushButton::clicked, this, &MainWindow::on_pushButtonLoadImage_clicked);

    connect(SingltoneClient::instance(), &SingltoneClient::responseReceived, this, [this](const QString& text) {
        ui->textEdit->append("> Server response:\n" + text);
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

    if (input.startsWith("solve")) {
        ui->textEdit->append("> Processing solution request: " + input);
        SingltoneClient::instance()->transmitCommand("SOLUTION:" + input);
    } else {
        ui->textEdit->append("> Processing encryption request: " + input);
        SingltoneClient::instance()->transmitCommand("ENCRYPT:" + input);
    }
}

void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        currentImagePath = filePath;
        ui->textEdit->append("> Image loaded: " + filePath);
    }
}
