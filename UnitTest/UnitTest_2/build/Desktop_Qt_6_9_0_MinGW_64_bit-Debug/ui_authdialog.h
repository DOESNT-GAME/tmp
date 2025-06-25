/********************************************************************************
** Form generated from reading UI file 'authdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHDIALOG_H
#define UI_AUTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AuthDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QTextEdit *textEditStatus;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonRegister;
    QPushButton *pushButtonLogin;

    void setupUi(QDialog *AuthDialog)
    {
        if (AuthDialog->objectName().isEmpty())
            AuthDialog->setObjectName("AuthDialog");
        AuthDialog->resize(350, 400);
        AuthDialog->setStyleSheet(QString::fromUtf8("background-color: #2E3440;\n"
"color: #D8DEE9;"));
        verticalLayout = new QVBoxLayout(AuthDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(AuthDialog);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #81A1C1;\n"
"    font-size: 16pt;\n"
"    font-weight: bold;\n"
"    qproperty-alignment: AlignCenter;\n"
"}"));

        verticalLayout->addWidget(labelTitle);

        groupBox = new QGroupBox(AuthDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 5px;\n"
"    margin-top: 10px;\n"
"    padding-top: 15px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px;\n"
"}"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        labelUsername = new QLabel(groupBox);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #D8DEE9;\n"
"}"));

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelUsername);

        lineEditUsername = new QLineEdit(groupBox);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 6px;\n"
"}"));

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditUsername);

        labelPassword = new QLabel(groupBox);
        labelPassword->setObjectName("labelPassword");
        labelPassword->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #D8DEE9;\n"
"}"));

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelPassword);

        lineEditPassword = new QLineEdit(groupBox);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 6px;\n"
"}"));
        lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditPassword);


        verticalLayout->addWidget(groupBox);

        textEditStatus = new QTextEdit(AuthDialog);
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

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButtonRegister = new QPushButton(AuthDialog);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4C566A;\n"
"    color: #D8DEE9;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5E81AC;\n"
"}"));

        horizontalLayout->addWidget(pushButtonRegister);

        pushButtonLogin = new QPushButton(AuthDialog);
        pushButtonLogin->setObjectName("pushButtonLogin");
        pushButtonLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #5E81AC;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #81A1C1;\n"
"}"));

        horizontalLayout->addWidget(pushButtonLogin);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AuthDialog);

        QMetaObject::connectSlotsByName(AuthDialog);
    } // setupUi

    void retranslateUi(QDialog *AuthDialog)
    {
        AuthDialog->setWindowTitle(QCoreApplication::translate("AuthDialog", "Login", nullptr));
        labelTitle->setText(QCoreApplication::translate("AuthDialog", "\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214!", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AuthDialog", "\320\224\320\265\321\202\320\260\320\273\320\270 \320\262\321\205\320\276\320\264\320\260:", nullptr));
        labelUsername->setText(QCoreApplication::translate("AuthDialog", "\320\233\320\276\320\263\320\270\320\275:", nullptr));
        labelPassword->setText(QCoreApplication::translate("AuthDialog", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("AuthDialog", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        pushButtonLogin->setText(QCoreApplication::translate("AuthDialog", "\320\222\320\276\320\271\321\202\320\270 \320\262 \320\260\320\272\320\272\320\260\321\203\320\275\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthDialog: public Ui_AuthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHDIALOG_H
