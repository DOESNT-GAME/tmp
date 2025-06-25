QT += testlib core network sql widgets qml

TARGET = UnitTest_Auth  # Изменили на единое имя
CONFIG += console c++17
CONFIG -= app_bundle

# Клиентские файлы
SOURCES += \
    Client/singletonclient.cpp \
    Tests/test_auth.cpp \
    Tests/main.cpp

HEADERS += \
    Client/singletonclient.h \
    Tests/test_auth.h

# Серверные файлы
SOURCES += \
    Server/mytcpserver.cpp \
    Server/dbmanager.cpp \
    Server/sha384.cpp

HEADERS += \
    Server/mytcpserver.h \
    Server/dbmanager.h \
    Server/sha384.h

# Для тестовой БД
DEFINES += TEST_DB=\"test_db.sqlite\"

QMAKE_CLEAN += *.o *.exe test_db.sqlite
