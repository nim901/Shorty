#include "shorty.h"
#include "ui_shorty.h"

Shorty::Shorty(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Shorty)
{
    ui->setupUi(this);
    ui->textEdit->installEventFilter(this);
    ui->label->setText("Welcome. Please open a file");
    data = new shortyModel();
    xmlFile = new xmlReader(*data);
}

Shorty::~Shorty()
{
    delete ui;
}

bool Shorty::eventFilter (QObject *obj, QEvent *event)
{
    if (obj == ui->textEdit && !keyList.isEmpty()) {
        if (event->type() == QEvent::KeyPress && !((QKeyEvent*)event)->isAutoRepeat()) { //key is pressed
            keysPressed++;
            if (!errorFlag) {
                keyPressEventHandler(event);
            }
            return true;
        }
        else if(event->type() == QEvent::KeyRelease) //key is relesed
        {
            if (!((QKeyEvent*)event)->isAutoRepeat()) {
                keysPressed--;
                keyReleaseEventHandler(event);
            }
            return true;
        }
        else {
            return true;
        }
    }
    // pass the event on to the parent class
    return QMainWindow::eventFilter(obj, event);
}

void Shorty::keyPressEventHandler(QEvent *event){
    qDebug(shorty_Main()) << "A key was pressed. we are now at location" << getLocation() << "and looking for"
                          << data->getCommandAt(getLocation());
    if (data->getCommandAt(getLocation()) == "Ctrl" && ((QKeyEvent*)event)->modifiers() && Qt::ControlModifier) {
        //if key is Ctrl
        qDebug(shorty_Main()) << "Ctrl was pressed. our location is" << getLocation() << "and now it'll be"
                              << getLocation()+1;
        paint(getLocation());
        setLocation(getLocation()+1);
    }
    else if (data->getCommandAt(getLocation()) == "Alt" && ((QKeyEvent*)event)->modifiers() && Qt::AltModifier) {
        //if key is Alt
        qDebug(shorty_Main()) << "Alt was pressed. our location is" << getLocation() << "and now it'll be"
                              << getLocation()+1;
        paint(getLocation());
        setLocation(getLocation()+1);
    }//shift
    else if (data->getCommandAt(getLocation()) == "Enter" &&
             (((QKeyEvent*)event)->key() == Qt::Key_Enter || ((QKeyEvent*)event)->key() == Qt::Key_Return)) {
        //if key is Enter
        qDebug(shorty_Main()) << "Enter was pressed. our location is" << getLocation() << "and now it'll be"
                              << getLocation()+1;
        paint(getLocation());
        setLocation(getLocation()+1);
    }
    else if (data->getCommandAt(getLocation()) == "ESC" && (((QKeyEvent*)event)->key() == Qt::Key_Escape)) {
        //if key is esc
        qDebug(shorty_Main()) << "Enter was pressed. our location is" << getLocation() << "and now it'll be"
                              << getLocation()+1;
        paint(getLocation());
        setLocation(getLocation()+1);
    }
    else { // key is not
        pressedKeys += ((QKeyEvent*)event)->key();
        qDebug(shorty_Main()) << ((QKeyEvent*)event)->key() << "was pressed. our location is" << getLocation()
                              << "and and the key that we are looking for is" << data->getCommandAt(getLocation());
        if ( pressedKeys.contains(toKey(data->getCommandAt(getLocation())))) {
            qDebug(shorty_Main()) << "We got a match. our location is" << getLocation() << "and now it'll be"
                                  << getLocation()+1;
            paint(getLocation());
            setLocation(getLocation()+1);
        }
        else {
            qDebug(shorty_Main()) << "No match for this key. turning on errorFlag";
            setLocation(getLocation()-1);
            errorPaint(getLocation());
            errorFlag = !errorFlag;
        }
    }
    if (getLocation() == keyList.count()) { //full match
        qDebug(shorty_Main()) << "Location is" << getLocation() << "Total count is" <<
                                 keyList.count() << "all keys for this shortcut are matched";
        load();
    }
}

bool Shorty::keyReleaseEventHandler(QEvent *event){
    qDebug(shorty_Main()) << "Key relese event. the key is" << ((QKeyEvent*)event)->key()
                          << "Our location is" << getLocation() << "now it'll be" << getLocation()-1;
    pressedKeys -= ((QKeyEvent*)event)->key();
    setLocation(getLocation()-1);
    qDebug(shorty_Main()) << "errorFlag is" << errorFlag;
    if (errorFlag) {
        if (keysPressed == 0) {
            qDebug(shorty_Main()) << "Clearing flag" << getLocation();
            errorFlag = !errorFlag;
            updateText();
        }
        else{
            qDebug(shorty_Main()) << "There are still" << keysPressed << "pressed keys";
            return true;
        }
    }
    else {
        qDebug() << keysPressed << "No errorFlag";
        unPaint(getLocation());
    }
    return true;
}

void Shorty::updateText()
{
    ui->textEdit->clear();
    qDebug(shorty_Main()) << "Updating text";
    QString text = QString(
                "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head>"
                "<body style=\"font-family:'MS Shell Dlg 2'; font-size:36pt; font-weight:400; font-style:normal;\">"
                "<p align=\"center\">"
                "%1"
                "</p></body></html>").arg(keyList.join(" + "));
    ui->textEdit->setText(text);
}

void Shorty::updateTitle()
{
    qDebug(shorty_Main()) << "updating title";
    ui->label->setText(data->getCommandName());
    QString _title = QString("Shorty %1 (%2/%3)").arg(data->getAppName())
            .arg(data->currentCommand()).arg(data->TotalCommands());
    this->setWindowTitle(_title);
}

void Shorty::load()
{
    setLocation(0);
    keyList.clear();
    keyList = data->getKeys();
    qDebug(shorty_Main()) << "Loaded new keys" << keyList;
    if (keyList.isEmpty()) {
        ui->label->setText("That's it for now!"); //need to check if file not loaded
        return;
    }
    updateTitle();
    updateText();
}

void Shorty::paint(int loc)
{
    qDebug(shorty_Main()) << "Adding some color to" << loc;
    QString goodHtml = "<font color=\"Green\">";
    QString endHtml = "</font>";
    keyList.replace(loc,goodHtml + keyList.at(loc) + endHtml);
    updateText();
}

void Shorty::errorPaint(int loc)
{
    qDebug(shorty_Main()) << "Wrong key at" << loc;
    keyList.replace(loc,data->getCommandAt(getLocation()));
    QString badHtml = "<font color=\"Red\">";
    QString endHtml = "</font>";
    QString text = QString(
                "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head>"
                "<body style=\"font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:400; font-style:normal;\">"
                "<p align=\"center\">"
                "%1"
                "</p></body></html>").arg(badHtml + "Release all keys and try again." + endHtml);
    ui->textEdit->setText(text);
}

void Shorty::unPaint(int loc)
{
    qDebug(shorty_Main()) << "No color for you!" << loc;
    keyList.replace(loc,data->getCommandAt(getLocation()));
    updateText();
}

uint Shorty::toKey(QString const & str) {
    qDebug(shorty_Main()) << "Translating" << str << "to key code";
    QKeySequence seq(str);
    uint keyCode;

    // We should only working with a single key here
    if(seq.count() == 1)
        keyCode = seq[0];
    else {
        // Should be here only if a modifier key (e.g. Ctrl, Alt) is pressed.
        assert(seq.count() == 0);

        // Add a non-modifier key "A" to the picture because QKeySequence
        // seems to need that to acknowledge the modifier. We know that A has
        // a keyCode ocommandVector 65 (or 0x41 in hex)
        seq = QKeySequence(str + "+A");
        assert(seq.count() == 1);
        assert(seq[0] > 65);
        keyCode = seq[0] - 65;
    }
    qDebug(shorty_Main()) << "Key code is" << keyCode;
    return keyCode;
}

void Shorty::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "",
                                                    tr("Shorty file (*.*)"));
    if (!fileName.isEmpty()) {
        qDebug(shorty_Main()) << "Cleaning data";
        data->clean();
        qDebug(shorty_Main()) << "calling xmlReader with" << fileName;
        xmlFile->OpenFile(fileName);
    }
    ui->textEdit->setFocus();
    load();
}
