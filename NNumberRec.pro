#-------------------------------------------------
#
# Project created by QtCreator 2018-04-11T19:28:50
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(printsupport): QT += printsupport

TARGET = NNumberRec
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

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/lib/TINN
INCLUDEPATH += $$PWD/src/plugins/scribble
INCLUDEPATH += $$PWD/src/plugins/barChartResult

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/numberrec.cpp \
    src/lib/TINN/Tinn.c \
    src/plugins/scribble/scribblearea.cpp \
    src/plugins/scribble/scribblewidget.cpp \
    src/plugins/barChartResult/barchartresult.cpp

HEADERS += \
    src/mainwindow.h \
    src/numberrec.h \
    src/lib/TINN/Tinn.h \
    src/plugins/scribble/scribblearea.h \
    src/plugins/scribble/scribblewidget.h \
    src/plugins/barChartResult/barchartresult.h

FORMS += \
    src/mainwindow.ui \
    src/plugins/scribble/scribblewidget.ui \
    src/plugins/barChartResult/barchartresult.ui

RESOURCES += \
    src/ressources/icons.qrc
