cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_AUTOMOC ON)

#Projet
project(Editeur)
#Chemin de l'executable
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_FIND_LIBRARY_SUFFIXES .a .so)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory bin)

#include
include_directories(${QT_INCLUDE})

#links
link_directories(${QT_LIB})

#Liste des fichiers sources
file(GLOB_RECURSE SOURCE_FILES src/*)

#Executable
add_executable(Editeur ${SOURCE_FILES})


#============    Qt5    =================#
find_package(Qt5Widgets)
find_package(Qt5Gui)
IF(Qt5Widgets_FOUND AND Qt5Gui_FOUND)

	qt5_use_modules(Editeur Widgets Gui)

ELSE()

#============    Qt4    =================#
	find_package(Qt4 REQUIRED)
	ADD_DEFINITIONS(${QT_DEFINITIONS})
	INCLUDE(${QT_USE_FILE})
	TARGET_LINK_LIBRARIES(Editeur ${QT_LIBRARIES})
ENDIF()
