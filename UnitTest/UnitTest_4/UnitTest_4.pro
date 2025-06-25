QT += testlib core widgets
CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = UnitTest_4
SOURCES += \
    main.cpp \
    sha384.cpp \
    test_sha384.cpp

HEADERS += \
    sha384.h \
    test_sha384.h
