#-------------------------------------------------
#
# Project created by QtCreator 2019-01-03T11:17:00
#
#-------------------------------------------------

QT       += core gui sql network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GBBStock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG -= debug_and_release
MOC_DIR = MOCS
OBJECTS_DIR = OBJS
RCC_DIR = QRC
UI_DIR = UI


SOURCES += \
        main.cpp \
        gbbmain.cpp \
    dbinterface.cpp \
    dialogproduct.cpp \
    calculator.cpp \
    diagadvsearch.cpp \
    csvreader.cpp \
    csvimporter.cpp \
    diagcsvimport.cpp \
    diagdbbkp.cpp \
    diagminstockselect.cpp \
    dbworkerthread.cpp \
    diagchangeinmultiplefields.cpp \
    diagwaitdboperation.cpp \
    diagventa.cpp \
    dropablelineedit.cpp \
    diagsalehistory.cpp

HEADERS += \
        gbbmain.h \
    global.h \
    dbinterface.h \
    dialogproduct.h \
    calculator.h \
    diagadvsearch.h \
    csvreader.h \
    csvimporter.h \
    diagcsvimport.h \
    diagdbbkp.h \
    diagminstockselect.h \
    dbworkerthread.h \
    diagchangeinmultiplefields.h \
    diagwaitdboperation.h \
    diagventa.h \
    dropablelineedit.h \
    diagsalehistory.h

FORMS += \
        gbbmain.ui \
    dialogproduct.ui \
    diagadvsearch.ui \
    diagcsvimport.ui \
    diagdbbkp.ui \
    diagminstockselect.ui \
    diagchangeinmultiplefields.ui \
    diagwaitdboperation.ui \
    diagventa.ui \
    diagsalehistory.ui
