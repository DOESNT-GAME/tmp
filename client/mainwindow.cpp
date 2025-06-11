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
        ui->textEdit->append("> Server response:\n" + text);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

double MainWindow::chordMethod(double a, double b, double epsilon) {
    double fa = a*a*a - a - 2; // Example function: x^3 - x - 2 = 0
    double fb = b*b*b - b - 2;
    double c = 0;

    while (fabs(b - a) > epsilon) {
        c = a - fa * (b - a) / (fb - fa);
        double fc = c*c*c - c - 2;

        if (fc * fa < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }
    return c;
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
    double a = ui->doubleSpinBoxA->value();
    double b = ui->doubleSpinBoxB->value();
    double epsilon = ui->doubleSpinBoxEpsilon->value();

    if (a >= b) {
        QMessageBox::warning(this, "Error", "Value 'a' must be less than 'b'");
        return;
    }

    // double result = chordMethod(a, b, epsilon);
    QString solution = QString("Not realized");
    ui->textEdit->append("> " + solution);
    SingletonClient::instance()->transmitCommand("EQUATION:" + solution);

}

void MainWindow::on_pushButtonLogout_clicked()
{
    AuthDialog *authDialog = new AuthDialog();
    authDialog->show();
    this->close();
}
