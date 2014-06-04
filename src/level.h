#ifndef __LEVEL__
#define __LEVEL__
#include "block.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QFile>
#include <QString>

class Level
{
	private:
		// Level dimensions
		int m_dimX;
		int m_dimY;
		// Level grid
		Block ***m_grid;
	public:
		Level(int dimX, int dimY);
		~Level();

		Block *getBlock(int x, int y);
		int getWidth();
		int getHeight();

		void setBlock(int x, int y, Block *b);
		void setBlock(int x, int y, std::string name);

		void save(QString fileName);
};
#endif
