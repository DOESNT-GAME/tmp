QT -= gui
QT += core network
QT += sql
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        dbmanager.cpp \
        main.cpp \
        mytcpserver.cpp \
        sha384.cpp

HEADERS += \
        dbmanager.h \
        mytcpserver.h \
        sha384.h
