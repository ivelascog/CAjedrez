#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T11:41:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagicChess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Multiplayer/Client.cpp \
    Multiplayer/Host.cpp \
    Multiplayer/MultiplayerBoard.cpp \
    Multiplayer/MultiplayerGame.cpp \
    Multiplayer/SocketHelper.cpp \
    Terrain/Types/Plains.cpp \
    Terrain/Types/Rocks.cpp \
    Terrain/Terrain.cpp \
    Units/Classes/Archer.cpp \
    Units/Classes/Horse.cpp \
    Units/Classes/King.cpp \
    Units/Classes/Soldier.cpp \
    Units/Army.cpp \
    Units/Unit.cpp \
    Board.cpp \
    Game.cpp \
    Menu.cpp \
    TerrainMap.cpp \
    UnitMap.cpp \
    UI/UIGame.cpp

HEADERS += \
        mainwindow.h \
    Multiplayer/Client.h \
    Multiplayer/Host.h \
    Multiplayer/MultiplayerBoard.h \
    Multiplayer/MultiplayerGame.h \
    Multiplayer/SocketHelper.h \
    Terrain/Types/Plains.h \
    Terrain/Types/Rocks.h \
    Terrain/Terrain.h \
    Terrain/TerrainList.h \
    Terrain/TerrainNames.h \
    Units/Classes/Archer.h \
    Units/Classes/Horse.h \
    Units/Classes/King.h \
    Units/Classes/Soldier.h \
    Units/Army.h \
    Units/Unit.h \
    Units/UnitList.h \
    Units/UnitNames.h \
    Board.h \
    Game.h \
    Menu.h \
    TerrainMap.h \
    UnitMap.h \
    mainwindow.h \
    UI/UIGame.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    Other/ToDo
