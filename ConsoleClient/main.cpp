#include <QtCore/QCoreApplication>
#include "singltoneclient.h"
#include <iostream>
#include <QString>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SingltoneClient::getInstance();
    std::string msg;
    std::cin>>msg;
    SingltoneClient::getInstance() ->
        sendMsgToServer(QString::fromStdString(msg));

    return a.exec();
}
