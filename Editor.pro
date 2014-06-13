QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app
DESTDIR = bin
OBJECTS_DIR = obj


SOURCES += \
    src/block.cpp \
    src/editor.cpp \
    src/init.cpp \
    src/level.cpp \
    src/main.cpp

HEADERS  +=src/block.h \
    src/editor.h \
    src/init.h \
    src/level.h
