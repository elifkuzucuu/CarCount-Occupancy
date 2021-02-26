#ifndef REPORTER_H
#define REPORTER_H

#include <QObject>

class Reporter : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.issd.report.interface")
public:
    Reporter();
    bool m_reportCreated = false;
    void sor();
    void writeReport(bool &controlValue);
    QString readJSon(int index);
public slots:
    bool isReportCreated();


};

#endif // REPORTER_H
