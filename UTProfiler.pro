#-------------------------------------------------
#
# Project created by QtCreator 2014-05-07T17:12:30
#
#-------------------------------------------------

QT       += core gui xml

QMAKE_CXXFLAGS += -std=c++0x
CONFIG +=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTProfiler
TEMPLATE = app


SOURCES += src/main.cpp\
        qt/mainwindow.cpp \
    src/uvmanager.cpp \
    src/uv.cpp \
    src/xmlio.cpp

HEADERS  += qt/mainwindow.h \
    src/uvmanager.hpp \
    src/uv.hpp \
    src/structures.hpp \
    src/manager.hpp \
    src/singleton.hpp \
    src/exceptions.hpp \
    src/xmlio.hpp \
    src/abstractio.hpp

FORMS    += qt/ui/mainwindow.ui
