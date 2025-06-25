QT += testlib widgets network sql

SOURCES += \
    src/regdialog.cpp \
    src/dbmanager.cpp \
    src/sha384.cpp \
    src/singletonclient.cpp \
    tests/main.cpp \
    tests/test_registration.cpp

HEADERS += \
    src/regdialog.h \
    src/dbmanager.h \
    src/sha384.h \
    src/singletonclient.h \
    mocks/mocksingletonclient.h \
    tests/test_registration.h

FORMS += src/regdialog.ui

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += testcase
TARGET = UnitTest_1

MOC_DIR = build/moc
UI_DIR = build/ui
OBJECTS_DIR = build/obj
DESTDIR = build
