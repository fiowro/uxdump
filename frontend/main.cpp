#include "start_program.h"
#include <QApplication>
#include "databasework.h"
#include <QtSql>
#include <QtSql/qsqlquery.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataBaseWork *DB = new DataBaseWork();
    DB->CreateBase();


      // ОТКРЫТИЕ ГЛАВНОЙ ФОРМЫ ПРОГРАММЫ

    Start_program w;
    w.show();



    return a.exec();
}
