DEFINES += QT_NO_NARROWING_CONVERSIONS_IN_CONNECT
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

QT += core
QT += gui
QT += widgets
QT += network

HEADERS += core/workspace.h
HEADERS += ui/modelworkspaceitem.h
HEADERS += ui/modelworkspace.h
HEADERS += ui/treeviewworkspace.h
HEADERS += ui/panelworkspace.h
HEADERS += ui/panelrequest.h
HEADERS += ui/panelresponse.h
HEADERS += ui/mainwindow.h

SOURCES += core/workspace.cpp
SOURCES += ui/modelworkspaceitem.cpp
SOURCES += ui/modelworkspace.cpp
SOURCES += ui/treeviewworkspace.cpp
SOURCES += ui/panelworkspace.cpp
SOURCES += ui/panelrequest.cpp
SOURCES += ui/panelresponse.cpp
SOURCES += ui/mainwindow.cpp
SOURCES += main.cpp

RESOURCES += assets/assets.qrc
