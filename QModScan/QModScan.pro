#-------------------------------------------------
#
# Project created by QtCreator 2018-11-19T13:54:31
#
#-------------------------------------------------

QT       += serialbus core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QModScan
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

CONFIG += c++11

SOURCES += \
        main.cpp \
    basedeviceconfig.cpp \
    tcpdeviceconfig.cpp \
    widgets/newconnectionwidget.cpp \
    widgets/mainwidget.cpp \
    model/modbusmodel.cpp \
    widgets/devicewidget.cpp \
    modbus/basemodbusclient.cpp \
    modbus/tcpmodbusclient.cpp \
    modbus/rtumodbusclient.cpp \
    rtudeviceconfig.cpp \
    loggingcategories.cpp

HEADERS += \
    basedeviceconfig.h \
    tcpdeviceconfig.h \
    widgets/newconnectionwidget.h \
    widgets/mainwidget.h \
    model/modbusmodel.h \
    widgets/devicewidget.h \
    modbus/basemodbusclient.h \
    modbus/tcpmodbusclient.h \
    modbus/rtumodbusclient.h \
    rtudeviceconfig.h \
    loggingcategories.h

FORMS += \
    widgets/newconnectionwidget.ui \
    widgets/mainwidgetui \
    widgets/devicewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
