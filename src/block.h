#ifndef __BLOCK__
#define __BLOCK__

#include <map>
#include <string>

class Block
{
	private:
		// Block name
		std::string m_name;
		// Block sprite
		std::string m_imageFile;
	public:
		// Block types (name->block)
		static std::map<std::string, Block*> TYPES;
		Block(std::string name, std::string imageFile);
		~Block();

		std::string getName();
		std::string getImageFile();

		static void initBlockTypes();
		static const int NB_TYPES = 14;
		static const int SPRITE_SIZE = 60;
};
#endif
