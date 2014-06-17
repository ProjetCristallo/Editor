Editor
======

Level Editor for the game Cristal Maze
--------------------------------------

# Features
* Level edition using a GUI
* Loading and saving levels
* Blocks can be added, removed or changed easily.
* Blocks can be set as unique

# Requirements
## Windows
None, the program comes with the needed dlls
## Linux
* Qt4 or Qt5, depending on the version of the executable

# Compilation
## Requirements
	* Qt4 or Qt5
	* cmake 2.8.8 (or higher) or qmake or QtCreator
## Default behavior
By default cmake will try to use Qt5 and will switch to Qt4 if Qt5 was not found.
## Options
	* Use the option -DQT5=OFF when running cmake to force the use of Qt4. 
