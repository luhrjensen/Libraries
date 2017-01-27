#-------------------------------------------------
#
# Project created by QtCreator 2012-01-08T13:54:55
#
#-------------------------------------------------

QT       += core gui

TARGET = qkclmtr
TEMPLATE = lib
CONFIG += staticlib
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
CONFIG += x86_64

SOURCES += QKClmtr.cpp \
    ../kclmtr/serialPort.cpp \
    ../kclmtr/KClmtr.cpp \
    ../kclmtr/Flicker.cpp \
    ../kclmtr/Measurement.cpp \
    ../kclmtr/Counts.cpp

HEADERS  += QKClmtr.h \
    ../kclmtr/serialPort.h \
    ../kclmtr/KClmtr.h \
    ../kclmtr/Flicker.h \
    ../kclmtr/matrix.h \
    ../kclmtr/Measurement.h \
    ../kclmtr/BlackMatrix.h \
    ../kclmtr/Counts.h \
    ../kclmtr/Enums.h \
    ../kclmtr/WRGB.h

win32: DESTDIR = ../bin/qt/win
macx: DESTDIR = ../bin/qt/mac
unix:!macx:!symbian:  DESTDIR = ../bin/qt/unix
