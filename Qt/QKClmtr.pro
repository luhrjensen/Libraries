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

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
    TARGET = qkclmtr
} else {
    DESTDIR = build/release
    TARGET = qkclmtr
}

SOURCES += QKClmtr.cpp \
    ../kclmtr/serialPort.cpp \
    ../kclmtr/KClmtr.cpp \

HEADERS  += QKClmtr.h \
    ../kclmtr/serialPort.h \
    ../kclmtr/KClmtr.h \








