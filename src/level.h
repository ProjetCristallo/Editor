#ifndef __LEVEL__
#define __LEVEL__
#include "block.h"
#include <iostream>
#include <fstream>

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

		void setBlock(int x, int y, Block *b);
		void setBlock(int x, int y, std::string name);

		void save(char *fileName);
};
#endif
