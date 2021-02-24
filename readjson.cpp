#include <QString>
#include <QDebug>
#include <QFile>


QString readJSon(int index)
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





