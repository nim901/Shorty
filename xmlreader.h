#ifndef XMLREADER_H
#define XMLREADER_H

#include <QtXml/QtXml>
#include <QtCore>
#include <QDebug>
#include "header.h"

class xmlReader
{
public:
    xmlReader(shortyModel &data);
    int OpenFile(QString fileName);
    int retrievElements(QDomElement root, QString tag);

private:
    QFile file;
    QDomDocument document;
    const QString Name = "Name";
    const QString Key = "Key";
    shortyModel &_data;
};

#endif // XMLREADER_H
