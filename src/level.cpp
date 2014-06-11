#include "level.h"

Level::Level(int dimX, int dimY)
{
	this->m_dimX = dimX;
	this->m_dimY = dimY;
	m_grid = new Block**[this->m_dimX];
	for(int i = 0 ; i < this->m_dimX ; i++)
	{
		m_grid[i] = new Block*[this->m_dimY];
		for(int j = 0 ; j < this->m_dimY ; j++)
		{
			m_grid[i][j] = Block::TYPES["Empty"];
		}
	}
}

Level::~Level()
{
	for(int i = 0 ; i < this->m_dimX ; i++)
	{
		delete m_grid[i];
	}
	delete m_grid;
}

Block *Level::getBlock(int x, int y)
{
	return this->m_grid[x][y];
}

int Level::getWidth()
{
	return this->m_dimX;
}

int Level::getHeight()
{
	return this->m_dimY;
}

void Level::setBlock(int x, int y, Block *b)
{
	if(x >= 0 && x < this->m_dimX && y >= 0 && y <= this->m_dimY)
	{
		this->m_grid[x][y] = b;
	}
	else
	{
		std::cerr << "Impossible de créer un bloc à " << x << ", " << y << " : position hors niveau.\n";
	}
}

void Level::setBlock(int x, int y, std::string name)
{
	Block *b = Block::TYPES[name];
	if(b != NULL)
	{
		setBlock(x,y,b);
	}
	else
	{
		std::cerr << "Impossible de créer le bloc "<< name << " à " << x << ", " << y << " : Type inconnu.\n";
	}
}

void Level::save(QString fileName)
{
	QFile file(fileName);
	if(file.open(QIODevice::WriteOnly))
	{
		for(int i = 0 ; i < this->m_dimX ; i++)
		{
			for(int j = 0 ; j < this->m_dimY ; j++)
			{
				std::string name = this->m_grid[i][j]->getName();
				if(name.compare("Empty") != 0)
				{
					Block *block = Block::TYPES[name];
					std::string args = block->getArguments();
					std::string identifier = block->getIdentifier();
					std::stringstream lineStream;
					lineStream << identifier << " " << i << " " << j << " " << args << "\n";
					std::string lineStr = lineStream.str();
					file.write(lineStr.c_str());
				}
			}
		}
		file.close();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Erreur : Impossible d'ouvrir le fichier "+fileName);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
	}
}

void Level::load(QString fileName)
{
	QFile file(fileName);
	if(file.open(QIODevice::ReadOnly))
	{
		this->clean();
		QTextStream in(&file);
		while(!in.atEnd())
		{
			QString line = in.readLine();
			QStringList args = line.split(" ");
			if(args.length() >= 3)
			{
				std::string name = args[0].toStdString();
				int x = args[1].toInt();
				int y = args[2].toInt();
				std::string arguments = "";
				if(args.length() == 4)
				{
					arguments = args[3].toStdString();
				}
				typedef std::map<std::string, Block*>::iterator it_blockMap;
				for(it_blockMap it = Block::TYPES.begin() ; it != Block::TYPES.end() ; it++)
				{
					Block *b = it->second;
					if(b->getIdentifier().compare(name) == 0 &&
						b->getArguments().compare(arguments) == 0)
					{
						this->m_grid[x][y] = b;
					}
				}
			}
		}
		file.close();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Erreur : Impossible d'ouvrir le fichier "+fileName);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
	}
}

void Level::clean()
{
	for(int i = 0 ; i < this->m_dimX ; i++)
	{
		for(int j = 0 ; j < this->m_dimY ; j++)
		{
			this->m_grid[i][j] = Block::TYPES["Empty"];
		}
	}
}
