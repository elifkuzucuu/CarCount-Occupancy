#include <QDebug>
#include <QObject>

#include <QtDBus>
#include <QDBusConnection>

#include "reporter.h"



Reporter :: Reporter()
{
    if( !QDBusConnection::sessionBus().registerService("org.issd.report.service") ) {
        qDebug() << "DBus registration failed" << QDBusConnection::sessionBus().lastError().message();
    } else {
        qDebug() << "DBus registration successful";
    }
    bool tRetval = QDBusConnection::sessionBus().registerObject("/report", "org.issd.report.interface", this, QDBusConnection::ExportAllContents);
    if (!tRetval) {
        qCritical() << "Couldn't register dbus interface on /main with org.issd.report.interface";
    }
    sor();
}

void Reporter::sor()
{
    QThread::msleep(20);

}

bool Reporter :: isReportCreated()
{
    qDebug() << "isReportedCreated a girdi";
    this->m_reportCreated = true;
    //writeReport(m_reportCreated);

    return true;

}
QString Reporter :: readJSon(int index)
{
    QString allFile;
    QFile file("Reporter.json");
    //file.setFileName("Reporter.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    allFile = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(allFile.toUtf8());
    QJsonObject allObject = document.object();

    QJsonValue value = allObject.value(QString("location"));
    QJsonArray specificObject = value.toArray();


    QJsonValue cityValue= specificObject.at(index)["city"];

    QString city = cityValue.toString();

    //    QJsonValue surnameValue= specificObject.at(0)["surname"];
    //    QString surname = surnameValue.toString();
    //    qDebug() << surname;
    //    QJsonValue ageValue= specificObject.at(0)["age"];
    //    int age = ageValue.toInt();
    //    qDebug() << age;

    return city;

}

void Reporter :: writeReport(bool &controlValue)
{

    QFile occupancyFile("Occupancy.txt");
    QFile carCountFile("CarCount.txt");
    QFile csvFile("occupancy-car.csv");
    QString occupancy, carCount;
    QStringList occupancyList,carCountList;
    int i;


    while(1)
    {
        qDebug() << "Selam, dosyaya yazmak için haber bekliyorum :)";
        if(controlValue)
        {
            qDebug() << "haber geldi,dosyaya yazıyorum.";
            if(!occupancyFile.open(QIODevice :: ReadOnly | QIODevice :: Text))
                return ;

            occupancy = occupancyFile.readAll();
            occupancyList = occupancy.split("\n");


            if(!carCountFile.open(QIODevice :: ReadOnly | QIODevice :: Text))
                return ;

            carCount = carCountFile.readAll();
            carCountList = carCount.split("\n");

            if(!csvFile.open(QIODevice :: WriteOnly | QIODevice :: Append))
                return ;

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
}
