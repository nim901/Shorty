#include "shortymodel.h"

shortyModel::shortyModel()
{

}

void shortyModel::add(int id, QVector<QString> vec)
{
    ShortcutMap.insert(id,vec);
}

QString shortyModel::getCommandName()
{
    return fullCommandVector.at(textOffset-1);
}

void shortyModel::clean()
{
    qDebug(shorty_Model()) << "Clean was called";
    location = 0;
    if (!fullCommandVector.isEmpty()) {
        qDebug(shorty_Model()) << "Removing keys and app name";
        fullCommandVector.clear();
        _appName = "";
    }
    qDebug(shorty_Model()) << "Nothing to do";
}

int shortyModel::currentCommand()
{
    return location;
}

int shortyModel::TotalCommands()
{
    return ShortcutMap.count();
}


QVector<QString> shortyModel::getVec()
{
    qDebug(shorty_Model()) << "Getting vector at location" << location
                           << "total count is" <<ShortcutMap.count();
    if (location < ShortcutMap.count()) {
        qDebug(shorty_Model()) << "Got keys" << ShortcutMap.value(location);
    return ShortcutMap.value(location++);
    }
    qDebug(shorty_Model()) << "No keys. returning empty vector";
    return QVector<QString>();
}

QStringList shortyModel::getKeys()
{
    fullCommandVector = getVec();
    qDebug(shorty_Model()) << "Sending keys";
    QStringList commandList = QStringList();
    if (!fullCommandVector.isEmpty()) {
    for (int i = textOffset; i < fullCommandVector.count(); i++) {
        qDebug(shorty_Model()) << "Copy vector to list. now at item" << i
                               << "That has the value of" << fullCommandVector.at(i);
        commandList.append(fullCommandVector.at(i));
    }
    }
    return commandList;
}

QString shortyModel::getCommandAt(int loc)
{
    return fullCommandVector.at(loc + textOffset); //loc + textOffset since we want the command
}

