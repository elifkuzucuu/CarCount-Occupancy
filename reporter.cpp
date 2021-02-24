#include <QDebug>
#include <QObject>
#include <QtDBus>
#include <QDBusConnection>


#include "reporter.h"


Reporter :: Reporter()
{

    if( !QDBusConnection::sessionBus().registerService("org.issd.writer.service") ) {
        qCritical() << "D-Bus registration failed" << QDBusConnection::sessionBus().lastError().message();
    }
    bool tRetval = QDBusConnection::sessionBus().registerObject("/main", "org.issd.writer.interface", this, QDBusConnection :: ExportAllContents);
    if (!tRetval) {
        qCritical() << "Couldn't register dbus interface on /main with org.issd.writer.interface";
    }
    else{
        qDebug() << "deneme constructor";
    }

}

bool Reporter :: isReportCreated()
{
    qDebug() << "isReportedCreated a girdi";
    m_reportCreated = true;

    return true;

}
