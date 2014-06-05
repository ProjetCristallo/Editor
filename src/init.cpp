#include "init.h"
#include "block.h"
#include <unistd.h>

std::string resourceDir = "../ressources/";
std::string levelDir = "../levels/";

bool init()
{
	// Check if the ini file exists
	if(access("editor.ini", 0) != 0)
	{
		return false;
	}

	readConfig();
	Block::initBlockTypes();
	return true;
}

void readConfig()
{
	QSettings settings("editor.ini", QSettings::IniFormat);
	settings.beginGroup("Config");
	resourceDir = settings.value("resourceDir").toString().toStdString();
	levelDir = settings.value("levelDir").toString().toStdString();
	settings.endGroup();
}
