#include "includes.h"
#include "widget.h"
#include <QtSql>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication app_master(argc, argv);

    Widget* mainwgd = new Widget(QCoreApplication::applicationDirPath() + "/test1.db");
    mainwgd->show();

    return app_master.exec();
}
