#ifndef SHORTCUTTREE_H
#define SHORTCUTTREE_H
#include <QMap>
#include <QString>
#include <QVector>
#include "header.h"

class shortyModel
{
public:
    shortyModel();
    void add(int, QVector<QString>);
    QStringList getKeys ();
    QString getCommandName();
    QString getAppName() { return _appName.isEmpty() ? "Error" : _appName; }
    void clean();
    void setAppName(QString name) { _appName = name; }
    int TotalCommands();
    int currentCommand();
    QString getCommandAt(int loc);

private:
    QVector<QString> getVec();
    QMap<int, QVector<QString> > ShortcutMap;
    int location = 0;
    QVector<QString> fullCommandVector;
    const int textOffset = 1;
    QString _appName;
};

#endif // SHORTCUTTREE_H
