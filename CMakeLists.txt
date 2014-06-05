cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_AUTOMOC ON)

#Projet
project(Editeur)
#Chemin de l'executable
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_FIND_LIBRARY_SUFFIXES .o .so)

find_package(Qt5Widgets)
find_package(Qt5Gui)

#include
include_directories(${QT_INCLUDE})

#links
link_directories(${QT_LIB})

#Liste des fichiers sources
file(GLOB_RECURSE SOURCE_FILES src/*)

#Executable
add_executable(Editeur ${SOURCE_FILES})

qt5_use_modules(Editeur Widgets Gui)
