QT += testlib core network sql
CONFIG += qt c++17 console
CONFIG -= app_bundle
CONFIG += debug

TARGET = UnitTest_3
TEMPLATE = app

SOURCES += \
    main.cpp \
    test_equation_solver.cpp \
    equation_solver.cpp \
    Client/singletonclient.cpp \
    Server/mytcpserver.cpp \
    Server/dbmanager.cpp \
    Server/sha384.cpp


HEADERS += \
    test_equation_solver.h \
    equation_solver.h \
    Client/singletonclient.h \
    Server/mytcpserver.h \
    Server/dbmanager.h \
    Server/sha384.h

