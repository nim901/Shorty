#include "shorty.h"
#include "shortylogging.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLoggingCategory::setFilterRules("shorty*.debug=true");
    Shorty w;
    w.show();

    return a.exec();
}
