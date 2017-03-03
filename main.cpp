#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/images/shishi2.png"));
	splash->show();
	Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
	splash->showMessage(QObject::tr("Setting up the main window..."),topRight,Qt::white);
	Sleep(1000);

	MainWindow w;
	w.show();
	splash->finish(&w);
	delete splash;	
	
	return a.exec();
}
