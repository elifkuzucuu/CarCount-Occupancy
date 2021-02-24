#ifndef REPORTER_H
#define REPORTER_H

#include <QObject>

class Reporter : public QObject
{

    Q_CLASSINFO("D-Bus Interface", "org.issd.writer.interface")
public:
    Reporter();
    bool m_reportCreated = false;
public slots:
    bool isReportCreated();

};

#endif // REPORTER_H
