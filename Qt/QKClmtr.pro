#-------------------------------------------------
#
# Project created by QtCreator 2012-01-08T13:54:55
#
#-------------------------------------------------

QT       += core gui

TARGET = QKClmtr
TEMPLATE = lib
CONFIG += staticlib
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
CONFIG += x86_64

SOURCES += QKClmtr.cpp \
    ../kclmtr/serialPort.cpp \
    ../kclmtr/KClmtr.cpp \

HEADERS  += QKClmtr.h \
    ../kclmtr/serialPort.h \
    ../kclmtr/KClmtr.h \


TARGET = qkclmtr

QHeader.files = QKClmtr.h
QHeader.path = ../bin/qt/Headers/
KClmtr_header.files += ../kclmtr/serialPort.h
KClmtr_header.files += ../kclmtr/KClmtr.h
KClmtr_header.path = ../bin/qt/Headers/kclmtr
INSTALLS += QHeader
INSTALLS += KClmtr_header

win32: DESTDIR = ../bin/qt/win
macx: DESTDIR = ../bin/qt/mac
