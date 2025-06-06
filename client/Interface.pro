QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += core network

RESOURCES += resources.qrc

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    reg.cpp \
    singltoneclient.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    reg.h \
    singltoneclient.h

FORMS += \
    login.ui \
    mainwindow.ui \
    reg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
