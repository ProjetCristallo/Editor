#ifndef __BLOCK__
#define __BLOCK__

#include <map>
#include <string>
#include <QIcon>
#include <vector>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <iostream>

class Block
{
	private:
		// Block name
		std::string m_name;
		// Block sprite
		QIcon *m_sprite;
		
		/* Elements to be put in the level file */
		// Block identifier
		std::string m_identifier;
		// Block arguments
		std::string m_arguments;

		void setIdentifier(std::string id);
		void setArguments(std::string arg);
	public:
		// Block types (name->block)
		static std::map<std::string, Block*> TYPES;
		Block(std::string name, std::string imageFile);
		~Block();

		std::string getName();
		QIcon *getSprite();
		std::string getIdentifier();
		std::string getArguments();

		static void initBlockTypes();
		static const int NB_TYPES = 14;
		static const int SPRITE_SIZE = 60;
};
#endif
