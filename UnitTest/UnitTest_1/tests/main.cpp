#include <QtTest>
#include <QApplication>

// Объявляем функцию тестирования
int testRegistration(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QApplication app(argc, argv);

    int status = 0;
    status |= testRegistration(argc, argv);

    return status;
}
