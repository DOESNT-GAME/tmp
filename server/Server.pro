QT -= gui
QT += core network sql
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        dbmanager.cpp \
        main.cpp \
        mytcpserver.cpp

HEADERS += \
        dbmanager.h \
        mytcpserver.h
