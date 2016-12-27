#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T09:31:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Algorithm_Homework_6_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jsoncpp.cpp

HEADERS  += mainwindow.h \
    bridge.h \
    json/json-forwards.h \
    json/json.h

FORMS    += mainwindow.ui

DISTFILES += \
    echarts.min.js
