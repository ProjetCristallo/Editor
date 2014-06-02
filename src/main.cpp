#include "editor.h"
#include "block.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	Block::initBlockTypes();
	QApplication app(argc,argv);
	Editor editor;
	editor.show();
	return app.exec();
}
