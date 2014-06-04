#include "block.h"

std::map<std::string, Block*> Block::TYPES;

Block::Block(std::string name, std::string imageFile)
{
	this->m_name = name;
	this->m_imageFile = imageFile;
	QString imagePath = QString::fromStdString(resourceDir);
	imagePath.append(QString::fromStdString(imageFile));
	this->m_sprite = new QIcon(imagePath);
}

Block::~Block()
{
}

std::string Block::getName()
{
	return this->m_name;
}

std::string Block::getImageFile()
{
	return this->m_imageFile;
}

QIcon *Block::getSprite()
{
	return this->m_sprite;
}

void Block::initBlockTypes()
{
	std::string blockNames[] = {
						"Simple",
						"Breakable",
						"Hole",
						"Unilateral_down",
						"Unilateral_up",
						"Unilateral_left",
						"Unilateral_right",
						"C_down",
						"C_up",
						"C_right",
						"C_left",
						"End",
						"Begin",
						"Empty"
						};
	std::string imageFiles[] = {
						"Simple.png",
						"Breakable.png",
						"Hole.png",
						"unilateral_down.png",
						"unilateral_up.png",
						"unilateral_left.png",
						"unilateral_right.png",
						"Change_down.png",
						"Change_up.png",
						"Change_right.png",
						"Change_left.png",
						"Star.png",
						"Bille.png",
						"Empty.png"
						};
	for(int i = 0 ; i < NB_TYPES ; i++)
	{
		Block *b = new Block(blockNames[i],imageFiles[i]);
		TYPES.insert(std::pair<std::string,Block*>(blockNames[i],b));
	}
}
