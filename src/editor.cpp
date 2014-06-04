#include "editor.h"

extern std::string resourceDir;

Editor::Editor(int dimX, int dimY):QMainWindow()
{
	this->m_dimX = dimX;
	this->m_dimY = dimY;

	this->m_sizeX = 300;
	this->m_sizeY = 200;

	this->m_posX = 0;
	this->m_posY = 0;
	
	this->m_currentBlock = "Simple";

	this->m_level = new Level(this->m_dimX, this->m_dimY);

	this->initUI();

	this->m_levelFile = "";
}

Editor::~Editor()
{
	delete m_level;
}

void Editor::initUI()
{
	// Central widget initialization
	this->m_mainWidget = new QWidget();
	this->m_mainWidget->resize(this->m_sizeX, this->m_sizeY);
	this->setCentralWidget(this->m_mainWidget);

	// Frames initialization
	this->m_buttonFrame = new QFrame(this);
	this->m_levelFrame = new QFrame(this);

	// Menu creation
	this->createMenu();

	// Window layout
	this->m_mainLayout = new QGridLayout();
	this->m_mainLayout->addWidget(this->m_levelFrame,0,0);
	this->m_mainLayout->addWidget(this->m_buttonFrame,0,1);
	// Set the layout
	this->m_mainWidget->setLayout(this->m_mainLayout);

	// Buttons creation
	this->createChoiceButtons();

	// Level view creation
	this->createLevelView();

	// Main window geometry
	this->m_sizeX = this->m_levelFrame->width() + this->m_buttonFrame->width();
	this->setGeometry(	this->m_posX, this->m_posY, 
						this->m_sizeX, this->m_sizeY);
	this->setWindowTitle("Editeur");
}

void Editor::createMenu()
{
	// Menu bar creation
	this->m_menuBar = this->menuBar();
	this->m_fileMenu = this->m_menuBar->addMenu("Fichier");
	// Save action
	QAction *saveAction = new QAction("Enregistrer", this);
	saveAction->setShortcut(QKeySequence("Ctrl+S"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveLevel()));
	this->m_fileMenu->addAction(saveAction);
	// Save as action
	QAction *saveAsAction = new QAction("Enregistrer sous", this);
	saveAsAction->setShortcut(QKeySequence("Ctrl+Shift+S"));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveLevelAs()));
	this->m_fileMenu->addAction(saveAsAction);

	// Exit app item
	QAction *exitAction = new QAction("Quitter", this);
	exitAction->setShortcut(QKeySequence("Ctrl+Q"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
	this->m_fileMenu->addAction(exitAction);
}

void Editor::createLevelView()
{
	// Signal mapper creation
	this->m_levelButtonsMapper = new QSignalMapper(this);
	// Level layout
	this->m_levelLayout = new QGridLayout();
	// Create the button array
	this->m_levelButtons = new QPushButton**[this->m_dimX];
	for(int i = 0 ; i < this->m_dimX ; i++)
	{
		this->m_levelButtons[i] = new QPushButton*[this->m_dimY];
		for(int j = 0 ; j < this->m_dimY ; j++)
		{
			Block *tmp = this->m_level->getBlock(i,j);

			// Create the button
			this->m_levelButtons[i][j] = new QPushButton("", this->m_levelFrame);
			this->m_levelButtons[i][j]->setIcon(*(tmp->getSprite()));
			this->m_levelButtons[i][j]->setIconSize(QSize(SPRITE_SIZE ,SPRITE_SIZE));

			QString args = "";
			args.append(QString::number(i));
			args.append(" ");
			args.append(QString::number(j));

			// Set the callback
			connect(this->m_levelButtons[i][j], SIGNAL(clicked()), this->m_levelButtonsMapper, SLOT(map()));
			this->m_levelButtonsMapper->setMapping(this->m_levelButtons[i][j], args);

			// Add the this->m_levelButtons[i][j] to the grid
			this->m_levelLayout->addWidget(this->m_levelButtons[i][j], j,i);
		}
	}
	// Connect the Signal mapper to the callback
	connect(this->m_levelButtonsMapper, SIGNAL(mapped(QString)), this, SLOT(setLevelBlock(QString)));
	// Set the layout
	this->m_levelFrame->setLayout(this->m_levelLayout);
}

void Editor::setLevelBlock(QString args)
{
	// Parse the arguments
	QStringList list = args.split(' ');
	// Get the name of the block to put
	std::string block = this->m_currentBlock;
	// Get the coordinates of the block
	int x = list[0].toInt();
	int y = list[1].toInt();
	// Delete the previous block in the level if the new block is unique
	for(int i = 0 ; i < uniqueBlocks.size() ; i++)
	{
		if(block == uniqueBlocks[i])
		{
			this->deleteUniqueBlock(block);
		}
	}
	// Set the block in the level
	this->m_level->setBlock(x,y,block);
	// Set the icon of the button
	Block *b = this->m_level->getBlock(x,y);
	this->m_levelButtons[x][y]->setIcon(*(b->getSprite()));
}

void Editor::createChoiceButtons()
{
	// Button frame layout
	this->m_buttonLayout = new QGridLayout();
	// Signal mapper creation
	this->m_blockButtonsMapper = new QSignalMapper(this);
	// Button creation
	int i = 0;
	int j = 0;
	typedef std::map<std::string, Block*>::iterator it_blockMap;
	for(it_blockMap it = Block::TYPES.begin() ; it != Block::TYPES.end() ; it++)
	{
		// Get the name of the block
		QString name = QString::fromStdString(it->second->getName());
		// Create the button
		QPushButton *button = new QPushButton("", this->m_mainWidget);
		button->setIcon(*(it->second->getSprite()));
		button->setIconSize(QSize(BUTTON_ICON_SIZE,BUTTON_ICON_SIZE));

		// Connect the button to a callback
		connect(button, SIGNAL(clicked()), this->m_blockButtonsMapper, SLOT(map()));
		this->m_blockButtonsMapper->setMapping(button, name);

		// Add the button to the grid
		this->m_buttonLayout->addWidget(button, i,j);

		// Update the index
		i++;
		if((i+1)*BUTTON_ICON_SIZE > this->m_sizeY)
		{
			j++;
			i = 0;
		}
	}
	// Connect the Signal mapper to the callback
	connect(this->m_blockButtonsMapper, SIGNAL(mapped(QString)), this, SLOT(setCurrentBlock(QString)));
	// Set the layout
	this->m_buttonFrame->setLayout(this->m_buttonLayout);
}

void Editor::quit()
{
	this->close();
}

void Editor::setCurrentBlock(QString block)
{
	this->m_currentBlock = block.toStdString();
}

void Editor::saveLevel()
{
	if(this->m_levelFile == "")
	{
		this->m_levelFile = QFileDialog::getSaveFileName(	this, 
				tr("Choix du fichier"), 
				QDir::currentPath(), 
				tr("text files (*.txt)")
				);
	}
	this->m_level->save(this->m_levelFile);
}

void Editor::saveLevelAs()
{
	this->m_levelFile = QFileDialog::getSaveFileName(	this, 
			tr("Choix du fichier"), 
			QDir::currentPath(), 
			tr("text files (*.txt)")
			);
	this->m_level->save(this->m_levelFile);
}

void Editor::deleteUniqueBlock(std::string block)
{
	// For each block of the level
	for(int i = 0 ; i < this->m_dimX ; i++)
	{
		for(int j = 0 ; j < this->m_dimY ; j++)
		{
			// If the block of the type we want, we make it empty
			if(this->m_level->getBlock(i,j)->getName() == block)
			{
				// Set the block in the level
				this->m_level->setBlock(i,j,"Empty");
				// Set the icon of the button
				Block *b = this->m_level->getBlock(i,j);
				this->m_levelButtons[i][j]->setIcon(*(b->getSprite()));
			}
		}
	}
}
