#include "editor.h"
#include "block.h"
#include "init.h"
#include <QApplication>

extern int dimX;
extern int dimY;

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	if(!init())
	{
		return 1;
	}
	Editor editor(dimX,dimY);
	editor.show();
	return app.exec();
}
