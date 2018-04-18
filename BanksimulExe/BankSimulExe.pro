#-------------------------------------------------
#
# Project created by QtCreator 2018-04-03T09:30:46
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankSimulExe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLPINCode-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lDLLPINCode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLPINCode-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lDLLPINCode

INCLUDEPATH += $$PWD/../DLLPINCode
DEPENDPATH += $$PWD/../DLLPINCode

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLSerialPort-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lDLLSerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLSerialPort-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lDLLSerialPort

INCLUDEPATH += $$PWD/../DLLSerialPort
DEPENDPATH += $$PWD/../DLLSerialPort

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DLLMySQLDLL-Desktop_Qt_5_10_0_MinGW_32bit-Debug/release/ -lDLLMySQLDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DLLMySQLDLL-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug/ -lDLLMySQLDLL

INCLUDEPATH += $$PWD/../DLLMySQL
DEPENDPATH += $$PWD/../DLLMySQL
