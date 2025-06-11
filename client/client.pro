QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += core network

RESOURCES += resources.qrc

SOURCES += \
        authdialog.cpp \
        authregcontainer.cpp \
        main.cpp \
        mainwindow.cpp \
        regdialog.cpp \
        singletonclient.cpp

HEADERS += \
    authdialog.h \
    authregcontainer.h \
    mainwindow.h \
    regdialog.h \
    singletonclient.h

FORMS += \
    authdialog.ui \
    mainwindow.ui \
    regdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
