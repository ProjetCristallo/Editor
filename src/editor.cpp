#include "editor.h"

extern const std::string resourceDir;

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
	// Exit app item
	QAction *exitAction = new QAction("Quitter", this);
	connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
	this->m_fileMenu->addAction(exitAction);
}

void Editor::createLevelView()
{
	// Level layout
	this->m_levelLayout = new QGridLayout();
	for(int i = 0 ; i < this->m_dimX ; i++)
	{
		for(int j = 0 ; j < this->m_dimY ; j++)
		{
			Block *tmp = this->m_level->getBlock(i,j);

			// Get the Sprite of the block
			QString imageFile = QString::fromStdString(tmp->getImageFile());
			QString imagePath = QString::fromStdString(resourceDir);
			imagePath.append(imageFile);

			// Create the button
			QPushButton *button = new QPushButton("", this->m_levelFrame);
			button->setIcon(QIcon(imagePath));
			button->setIconSize(QSize(SPRITE_SIZE ,SPRITE_SIZE));

			// Add the button to the grid
			this->m_levelLayout->addWidget(button, j,i);
		}
	}
	this->m_levelFrame->setLayout(this->m_levelLayout);
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
		// Get the Sprite of the block
		QString imageFile = QString::fromStdString(it->second->getImageFile());

		// Make the path to the sprite
		QString imagePath = QString::fromStdString(resourceDir);
		imagePath.append(imageFile);

		// Create the button
		QPushButton *button = new QPushButton("", this->m_mainWidget);
		button->setIcon(QIcon(imagePath));
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
