#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T16:09:49
#
#-------------------------------------------------

QT       += core gui
QT       += sql

INCLIDEPATH += ./qwt
LIBS += -lqwt
CONFIG += qwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ver3
TEMPLATE = app


SOURCES += main.cpp\
        start_program.cpp \
    add_log.cpp \
    databasework.cpp


HEADERS  += start_program.h \
    add_log.h \
    databasework.h

FORMS    += start_program.ui \
    add_log.ui
