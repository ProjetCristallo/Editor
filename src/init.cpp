#include "init.h"
#include "block.h"
#include <unistd.h>
#include <QFile>

std::string resourceDir = "./ressources/";
std::string levelDir = "../levels/";

bool init()
{
	// Check if the ini file exists
	QFile f("editor.ini");
	if(!f.exists())
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
