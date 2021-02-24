#include <QCoreApplication>
#include <QFile>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>

#include "readjson.cpp"
#include "reporter.h"


void registerDbus(QCoreApplication *app){
    Q_UNUSED(app);

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Reporter reporter;
    QFile occupancyFile("Occupancy.txt");
    QFile carCountFile("CarCount.txt");
    QFile csvFile("occupancy-car.csv");
    QString occupancy, carCount;
    QStringList occupancyList,carCountList;
    int i;



    registerDbus(&a);
    while(1)
    {
        if(reporter.m_reportCreated)
        {
            if(!occupancyFile.open(QIODevice :: ReadOnly | QIODevice :: Text))
                return 0;

            occupancy = occupancyFile.readAll();
            occupancyList = occupancy.split("\n");


            if(!carCountFile.open(QIODevice :: ReadOnly | QIODevice :: Text))
                return 0;

            carCount = carCountFile.readAll();
            carCountList = carCount.split("\n");

            if(!csvFile.open(QIODevice :: WriteOnly | QIODevice :: Append))
                return 0;

            QString city;
            for(i = 0 ; i < 100 ; i++)
            {
                QTextStream stream(&csvFile);
                if(i == 0)
                {

                    stream << "Title" << "\t" << "Car Count" << "\t" << "Occupancy" << "\n";
                }

                if(i<50)
                    city = readJSon(0);
                else {
                    city = readJSon(1);
                }

                stream << city << "\t" << carCountList[i] << "\t" << occupancyList[i] << "\n";



            }

        }
        QThread :: sleep(2);
    }





    return a.exec();
}
