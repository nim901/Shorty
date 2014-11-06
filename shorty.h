#ifndef SHORTY_H
#define SHORTY_H

#include <QMainWindow>
#include <QStringList>
#include <QEvent>
#include <QtGui>
#include <assert.h>
#include "xmlreader.h"
#include <QFileDialog>
#include "header.h"

namespace Ui {
class Shorty;
}

class Shorty : public QMainWindow
{
    Q_OBJECT

public:
    explicit Shorty(QWidget *parent = 0);
    ~Shorty();
    void setLocation(int loc) { loc > 0 ? _currentLocation = loc: _currentLocation = 0; }
    int getLocation() { return _currentLocation; }
    shortyModel *data;
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_actionOpen_triggered();

private:
    Ui::Shorty *ui;
    QStringList keyList;
    uint toKey(QString const & str);
    QSet<int> pressedKeys;
    int _currentLocation = 0;
    void paint(int loc);//will be combined into one function
    void unPaint(int loc);
    void errorPaint(int loc);
    void updateText();
    void updateTitle();
    void load();
    xmlReader *xmlFile;
    int keysPressed = 0;
    bool errorFlag = false;
    void keyPressEventHandler(QEvent *);
    bool keyReleaseEventHandler(QEvent *);
};

#endif // SHORTY_H
