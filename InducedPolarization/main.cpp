#include "InducedPolarization.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "Timer.h"
#include <crtdbg.h>
#include <QDir>
//#include <vld.h>
using namespace std;
int main(int argc, char *argv[])
{
	//enableMemLeakCheck();

	//_CrtSetBreakAlloc(1568901);

    QApplication a(argc, argv);

    InducedPolarization w;
    w.show();

	//qInstallMessageHandler(outputMessage);

    return a.exec();
}
