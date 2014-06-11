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
#include <QSplitter>
#include <QFrame>
#include <QFileDialog>
#include <QKeySequence>

#include "level.h"
#include "block.h"

#include <string>
#include <iostream>
#include <vector>

extern std::vector<std::string> uniqueBlocks;

class Editor: public QMainWindow
{
	Q_OBJECT

	private:
		static const int BUTTON_ICON_SIZE = 30;
		static const int SPRITE_SIZE = 30;
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
		// Button frame
		QFrame *m_buttonFrame;
		// Level frame
		QFrame *m_levelFrame;
		// Level view widget
		QWidget *m_levelWidget;
		QPushButton ***m_levelButtons;

		// Main widget layout
		QGridLayout *m_mainLayout;
		// Button frame layout
		QGridLayout *m_buttonLayout;
		// Level frame layout
		QGridLayout *m_levelLayout;

		// Signal mapper for the choice buttons
		QSignalMapper *m_blockButtonsMapper;
		// Signal mapper for the level buttons
		QSignalMapper *m_levelButtonsMapper;

		// Menu bar
		QMenuBar *m_menuBar;
		QMenu *m_fileMenu;

		// File name for the level
		QString m_levelFile;

		// UI initialization
		void initUI();
		void createMenu();
		void createChoiceButtons();
		void createLevelView();
		void deleteUniqueBlock(std::string block);
		void cleanLevel();

	public slots:
		void quit();
		void setCurrentBlock(QString block);
		void setLevelBlock(	QString args);
		void openLevel();
		void saveLevel();
		void saveLevelAs();
		void newLevel();
	public:
		Editor(int dimX = 10, int dimY = 8);
		~Editor();
};
#endif
