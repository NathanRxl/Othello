CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(Othello)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(Qt5Widgets)

SET(Othello_SOURCES cpp/main.cpp
					cpp/utils.cpp
					cpp/HomeWindow.cpp
					cpp/GameWindow.cpp
					cpp/ClickableLabel.cpp
                    cpp/Game.cpp)
SET(Othello_HEADERS headers/utils.h
					headers/HomeWindow.h
					headers/GameWindow.h
					headers/ClickableLabel.h
                    headers/Game.h)

ADD_EXECUTABLE(Othello ${Othello_SOURCES} ${Othello_HEADERS})
TARGET_LINK_LIBRARIES(Othello Qt5::Widgets)
INCLUDE_DIRECTORIES(headers)