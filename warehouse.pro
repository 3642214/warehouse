#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T15:19:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = warehouse
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    db.cpp \
    addclass.cpp

HEADERS  += mainwindow.h \
    db.h \
    addclass.h

FORMS    += mainwindow.ui \
    addclass.ui

OTHER_FILES += \
    ico.rc

RC_FILE = ico.rc
