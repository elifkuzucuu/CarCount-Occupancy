#include <QCoreApplication>
#include <QFile>
#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>

#include "readjson.cpp"
#include "reporter.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Reporter reporter;
    QThread writeThread;


    QObject::connect(&writeThread, &QThread::started, [&](){
        reporter.writeReport(reporter.m_reportCreated);

    });
    writeThread.start();



    return a.exec();
}
