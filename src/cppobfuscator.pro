#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T20:24:00
#
#-------------------------------------------------

QT       += core

QT       -= gui

CONFIG += c++11

TARGET = cppobfuscator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    obfuscator.cpp \
    RemoveMultyLineComments.cpp \
    RemoveSingleLineComments.cpp \
    RemoveEmptyStrings.cpp \
    RemoveTrailingSpacers.cpp \
    RemoveLeadingSpacers.cpp \
    RemoveInsideSpacers.cpp \
    RemoveLineSpliting.cpp \
    ReplaceByTrigraphs.cpp \
    RemoveLineFeed.cpp \
    ReplaceCharByDigit.cpp \
    StringSplitter.cpp

HEADERS += \
    obfuscator.h \
    RemoveMultyLineComments.h \
    RemoveSingleLineComments.h \
    RemoveEmptyStrings.h \
    RemoveTrailingSpacers.h \
    RemoveLeadingSpacers.h \
    RemoveInsideSpacers.h \
    RemoveLineSpliting.h \
    ReplaceByTrigraphs.h \
    RemoveLineFeed.h \
    ReplaceCharByDigit.h \
    StringSplitter.h
