#include "editor.h"

const std::string resourceDir = "../ressources/";

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
	// Main window geometry
	this->setGeometry(	this->m_posX, this->m_posY, 
						this->m_sizeX, this->m_sizeY);
	this->setWindowTitle("Editeur");
	
	// Central widget initialization
	this->m_mainWidget = new QWidget();
	this->m_mainWidget->resize(this->m_sizeX, this->m_sizeY);
	this->setCentralWidget(this->m_mainWidget);

	// Menu bar creation
	this->m_menuBar = this->menuBar();
	this->m_fileMenu = this->m_menuBar->addMenu("Fichier");
	// Exit app item
	QAction *exitAction = new QAction("Quitter", this);
	connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
	this->m_fileMenu->addAction(exitAction);
	// Window layout
	this->m_layout = new QGridLayout();
	// Signal mapper creation
	m_blockButtonsMapper = new QSignalMapper(this);
	// Button creation
	int i = 0;
	int j = 0;
	typedef std::map<std::string, Block*>::iterator it_blockMap;
	for(it_blockMap it = Block::TYPES.begin() ; it != Block::TYPES.end() ; it++)
	{
		QString name = QString::fromStdString(it->second->getName());
		QString imageFile = QString::fromStdString(it->second->getImageFile());
		QString imagePath = QString::fromStdString(resourceDir);
		imagePath.append(imageFile);
		// TODO : Icons (resourceDir+imageFile)
		QPushButton *button = new QPushButton("", this->m_mainWidget);
		button->setIcon(QIcon(imagePath));
		button->setIconSize(QSize(BUTTON_ICON_SIZE,BUTTON_ICON_SIZE));
		this->m_layout->addWidget(button, i,j);
		j++;
		if((j+1)*BUTTON_ICON_SIZE > this->m_sizeY)
		{
			i++;
			j = 0;
		}
	}
	this->m_mainWidget->setLayout(this->m_layout);
}

void Editor::quit()
{
	this->close();
}

void Editor::setCurrentBlock(std::string block)
{
	this->m_currentBlock = block;
}
