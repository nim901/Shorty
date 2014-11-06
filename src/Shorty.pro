#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T14:31:57
#
#-------------------------------------------------

QT       += core gui xml
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shorty
TEMPLATE = app


SOURCES += main.cpp\
        shorty.cpp \
    xmlreader.cpp \
    shortylogging.cpp \
    shortymodel.cpp

HEADERS  += shorty.h \
    xmlreader.h \
    shortylogging.h \
    shortymodel.h \
    header.h

FORMS    += shorty.ui
