#include "xmlreader.h"

xmlReader::xmlReader(shortyModel &data) :
    _data(data)
{
}

int xmlReader::OpenFile(QString fileName)
{
    // Open a file for reading
    qCDebug(shorty_Reader) << "Trying to open" << fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCCritical(shorty_Reader) << "Failed to open the file for reading.";
        return -1;
    }
    else
    {
        // loading
        if(!document.setContent(&file))
        {
            qCCritical(shorty_Reader) << "Failed to load the file for reading.";
            return -1;
        }
        file.close();
    }
    QDomElement root = document.documentElement();
    retrievElements(root, "Shortcut");

    qCDebug(shorty_Reader) << "Reading finished";
    file.close();
    return 0;
}

int xmlReader::retrievElements(QDomElement root, QString tag)
{
    QVector<QString> appKeys;
    _data.setAppName(root.nodeName());
    QDomNodeList nodes = root.elementsByTagName(tag);
    qCDebug(shorty_Reader) << "There are" << nodes.count() << "nodes with the tag" << tag;
    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode domNode = nodes.at(i);
        if(domNode.isElement())
        {
            QDomElement element = domNode.toElement();
            qCDebug(shorty_Reader) << "The element at" << i << "has the tag" << element.tagName() << "and attribute" << element.attribute("id");
            if (element.tagName() != tag || element.attribute("id").isEmpty()) {
                qCCritical(shorty_Reader) << "The element at" << i << "should be" << tag
                                          << "with ID attribute" << "but it's" << element.tagName()
                                          << "and the attribute is" << element.attribute("id");
                return -1;
            }
            if (element.hasChildNodes()) { //if there are child nodes
                QDomNodeList childNodes = element.childNodes();
                qCDebug(shorty_Reader) << element.tagName() << "has" << childNodes.count() << "child nodes. now reading the first";
                QDomNode childNod = childNodes.at(0);
                while (!childNod.isNull()) {
                    if(childNod.isElement()) {
                        QDomElement childElement = childNod.toElement();
                        if (childElement.tagName() == Name) {
                            //should check that there is only one name
                            qCDebug(shorty_Reader) << "Shortcut name" << childElement.text();
                            appKeys.append(childElement.text());
                        }
                        else if (childElement.tagName() == Key) {
                           qCDebug(shorty_Reader) << "Key name" << childElement.text();
                           appKeys.append(childElement.text());
                        }
                        else {
                            qCCritical(shorty_Reader) << "The element tag name should be either 'Name' or 'Key' but it's" << childElement.text();
                            return -1;
                        }
                        qCDebug(shorty_Reader) << "Calling for next sibling";
                        childNod = childNod.nextSibling();
                    }
                }
            }
            qDebug() << "Adding" << element.attribute("id").toInt() << element.tagName();
            _data.add(element.attribute("id").toInt(), appKeys);
            appKeys.clear();//clear for next run
        }

    }
    qCDebug(shorty_Reader) << "Finished reading the file";
    return 0;
}

