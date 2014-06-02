#ifndef __EDITOR__
#define __EDITOR__
#include <QMainWindow>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QSignalMapper>
#include <QIcon>
#include <QPushButton>
#include <QString>

#include "level.h"
#include "block.h"

#include <string>
#include <iostream>

class Editor: public QMainWindow
{
	Q_OBJECT

	private:
		static const int BUTTON_ICON_SIZE = 30;
		// Level dimensions
		int m_dimX;
		int m_dimY;
		// Window size
		int m_sizeX;
		int m_sizeY;
		// Window position
		int m_posX;
		int m_posY;
		// Selected block
		std::string m_currentBlock;
		// Level grid
		Level *m_level;

		// Main Widget
		QWidget *m_mainWidget;
		// Main widget layout
		QGridLayout *m_layout;
		// Signal mapper for the buttons
		QSignalMapper *m_blockButtonsMapper;

		// Menu bar
		QMenuBar *m_menuBar;
		QMenu *m_fileMenu;
		
		// UI initialization
		void initUI();

	public slots:
		void quit();
		void setCurrentBlock(std::string block);
	public:
		Editor(int dimX = 10, int dimY = 8);
		~Editor();
};
#endif
