DEFINES += QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

QT += core
QT += gui
QT += widgets
QT += network

HEADERS += panelrequest.h
HEADERS += modelworkspace.h
HEADERS += modelworkspaceitem.h
HEADERS += panelworkspace.h
HEADERS += treeviewworkspace.h
HEADERS += workspace.h
HEADERS += panelresponse.h
HEADERS += mainwindow.h

SOURCES += panelrequest.cpp
SOURCES += modelworkspace.cpp
SOURCES += modelworkspaceitem.cpp
SOURCES += panelworkspace.cpp
SOURCES += treeviewworkspace.cpp
SOURCES += workspace.cpp
SOURCES += panelresponse.cpp
SOURCES += mainwindow.cpp
SOURCES += main.cpp

RESOURCES += assets/assets.qrc
