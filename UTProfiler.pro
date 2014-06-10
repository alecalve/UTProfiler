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
    src/uv.cpp \
    src/xmlio.cpp \
    qt/uvdisplaywidget.cpp \
    qt/changesemestredialog.cpp \
    qt/addsemestredialog.cpp \
    qt/changecreditsdialog.cpp \
    qt/displaywidget.cpp \
    qt/notedisplaywidget.cpp \
    qt/categoriedisplaywidget.cpp \
    qt/adduvdialog.cpp \
    qt/addcategoriedialog.cpp \
    qt/addnotedialog.cpp

HEADERS  += qt/mainwindow.h \
    src/uvmanager.hpp \
    src/uv.hpp \
    src/structures.hpp \
    src/manager.hpp \
    src/singleton.hpp \
    src/exceptions.hpp \
    src/xmlio.hpp \
    src/abstractio.hpp \
    qt/uvdisplaywidget.h \
    qt/changesemestredialog.h \
    src/formation.hpp \
    src/dossier.hpp \
    src/semestre.hpp \
    qt/addsemestredialog.h \
    qt/changecreditsdialog.h \
    qt/displaywidget.h \
    qt/notedisplaywidget.h \
    qt/categoriedisplaywidget.h \
    qt/adduvdialog.h \
    qt/addcategoriedialog.h \
    qt/addnotedialog.h

FORMS    += qt/ui/mainwindow.ui \
    qt/ui/changesemestredialog.ui \
    qt/ui/addsemestredialog.ui \
    qt/ui/changecreditsdialog.ui \
    qt/ui/displaywidget.ui \
    qt/ui/adduvdialog.ui \
    qt/ui/addcategoriedialog.ui \
    qt/ui/addnotedialog.ui

RESOURCES += \
    qt/icons.qrc
