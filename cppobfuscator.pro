#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T20:24:00
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cppobfuscator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    obfuscator.cpp \
    RemoveMultyLineComments.cpp \
    RemoveSingleLineComments.cpp \
    RemoveEmptyStrings.cpp

HEADERS += \
    obfuscator.h \
    RemoveMultyLineComments.h \
    RemoveSingleLineComments.h \
    RemoveEmptyStrings.h
