#include "editor.h"
#include "block.h"
#include "init.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	init();
	Editor editor;
	editor.show();
	return app.exec();
}
