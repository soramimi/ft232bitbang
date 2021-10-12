TARGET = wpins
TEMPLATE = app
CONFIG += console
CONFIG -= qt

DESTDIR = $$PWD/_bin

INCLUDEPATH += /usr/local/include/libftdi1
LIBS += -L /usr/local/lib -l ftdi1

SOURCES += \
	wpins.cpp
