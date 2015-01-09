PROJECT(Tavenard)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FILE(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(Qt5.1.1)
SET(Tavenard_SOURCES main.cpp ma_fenetre.cpp othelloWindow.cpp Hlable.cpp)
SET(Tavenard_HEADERS ma_fenetre.h othelloWindow.h Hlabel.h)
FIND_PACKAGE(Imagine)

ImagineAddExecutable(Tavenard main.cpp ma_fenetre.cpp ma_fenetre.h othelloWindow.cpp othelloWindow.h Hlabel.cpp Hlabel.h)
ImagineUseModules(Tavenard Graphics)

