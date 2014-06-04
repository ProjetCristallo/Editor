#include "editor.h"
#include "block.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	Block::initBlockTypes();
	Editor editor;
	editor.show();
	return app.exec();
}
