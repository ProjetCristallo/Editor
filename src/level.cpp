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

void Level::save(char *fileName)
{
	std::ofstream file;
	file.open(fileName);
}
