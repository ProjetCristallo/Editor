#include "block.h"

std::string resourceDir = "../ressources/";
std::map<std::string, Block*> Block::TYPES;
std::vector<std::string> uniqueBlocks;

Block::Block(std::string name, std::string imageFile)
{
	this->m_name = name;
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

QIcon *Block::getSprite()
{
	return this->m_sprite;
}

void Block::initBlockTypes()
{
	QSettings settings("editor.ini", QSettings::IniFormat);
	settings.beginGroup("Config");
	resourceDir = settings.value("resourceDir").toString().toStdString();
	settings.endGroup();

	settings.beginGroup("Blocks");
	const QStringList childKeys = settings.childKeys();
	foreach(const QString &childKey, childKeys)
	{
		std::string name = childKey.toStdString();
		std::string imageFile = settings.value(childKey).toString().toStdString();

		Block *b = new Block(name,imageFile);
		TYPES.insert(std::pair<std::string,Block*>(name,b));
	}
	settings.endGroup();

	uniqueBlocks.push_back("Begin");
	uniqueBlocks.push_back("End");
}
