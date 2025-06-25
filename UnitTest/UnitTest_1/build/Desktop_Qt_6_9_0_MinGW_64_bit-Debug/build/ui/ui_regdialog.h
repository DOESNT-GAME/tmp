/********************************************************************************
** Form generated from reading UI file 'regdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGDIALOG_H
#define UI_REGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditPassword;
    QTextEdit *textEditStatus;
    QPushButton *pushButtonRegister;
    QPushButton *pushButtonBackToLogin;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(350, 354);
        RegisterDialog->setStyleSheet(QString::fromUtf8("background-color: #2E3440;\n"
"color: #D8DEE9;"));
        verticalLayout = new QVBoxLayout(RegisterDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(RegisterDialog);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #81A1C1;\n"
"    font-size: 16pt;\n"
"    font-weight: bold;\n"
"    qproperty-alignment: AlignCenter;\n"
"}"));

        verticalLayout->addWidget(labelTitle);

        lineEditUsername = new QLineEdit(RegisterDialog);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"}"));

        verticalLayout->addWidget(lineEditUsername);

        lineEditPassword = new QLineEdit(RegisterDialog);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"}"));
        lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(lineEditPassword);

        textEditStatus = new QTextEdit(RegisterDialog);
        textEditStatus->setObjectName("textEditStatus");
        textEditStatus->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #3B4252;\n"
"    color: #A3BE8C;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"}"));
        textEditStatus->setReadOnly(true);

        verticalLayout->addWidget(textEditStatus);

        pushButtonRegister = new QPushButton(RegisterDialog);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #5E81AC;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #81A1C1;\n"
"}"));

        verticalLayout->addWidget(pushButtonRegister);

        pushButtonBackToLogin = new QPushButton(RegisterDialog);
        pushButtonBackToLogin->setObjectName("pushButtonBackToLogin");
        pushButtonBackToLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4C566A;\n"
"    color: #D8DEE9;\n"
"    border-radius: 4px;\n"
"    padding: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5E81AC;\n"
"}"));

        verticalLayout->addWidget(pushButtonBackToLogin);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Registration", nullptr));
        labelTitle->setText(QCoreApplication::translate("RegisterDialog", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        lineEditUsername->setText(QString());
        lineEditUsername->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("RegisterDialog", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("RegisterDialog", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        pushButtonBackToLogin->setText(QCoreApplication::translate("RegisterDialog", "\320\236\320\261\321\200\320\260\321\202\320\275\320\276 \320\272\320\276 \320\262\321\205\320\276\320\264\321\203 \320\262 \320\260\320\272\320\272\320\260\321\203\320\275\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGDIALOG_H
