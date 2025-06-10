#include "authregcontainer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    AuthRegContainer container;
    container.show();
    return a.exec();
}
