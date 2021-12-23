DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

QT += core
QT += gui
QT += widgets
QT += network

HEADERS += panelrequest.h
HEADERS += panelresponse.h
HEADERS += mainwindow.h

SOURCES += panelrequest.cpp
SOURCES += panelresponse.cpp
SOURCES += mainwindow.cpp
SOURCES += main.cpp
