#include <QtCore>
#include <iostream>
#include <QMutexLocker>

#include "cloudthread.h"
CloudThread::CloudThread()
{
}

void CloudThread::run()
{
	process.apply();

	emit setActionEnable(true);
}

void CloudThread::stop()
{
	terminate();
}

void CloudThread::test()
{
	QThread::sleep(5);
}