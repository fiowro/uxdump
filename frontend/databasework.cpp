#include "databasework.h"

DataBaseWork::DataBaseWork()
{
    //***УСТАНОВКА СОЕДИНЕНИЯ С БАЗОЙ ДАННЫХ***

        QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");

        QString pathToDB = QDir::currentPath()+QString("/db.sqlite");
        dbase.setDatabaseName(pathToDB);

        //***ПРОВЕРКА ОТКРЫТИЯ БАЗЫ ДАННЫХ***

        if(!dbase.open()) {
            qDebug() << "Ошибка базы данных";

        }
}

void DataBaseWork:: CreateBase()

{
//***СОЗДАНИЕ ТАБЛИЦЫ БАЗЫ ДАННЫХ***

    QSqlQuery query;
    QString str = "CREATE TABLE person("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "login VARCHAR(150), sex CHAR, age INTEGER"
            ");";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str))
        qDebug() << "Невозможно создать таблицу 1";

    QString str1 = "CREATE TABLE test("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "name VARCHAR(150), payhTest VARCHAR(150)"
            ");";


    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str1))
        qDebug() << "Невозможно создать таблицу 2";

    QString str2 = "CREATE TABLE software("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "name VARCHAR(150)"
            ");";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str2))
        qDebug() << "Невозможно создать таблицу 3";

    QString str3 = "CREATE TABLE logs("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "id_person INTEGER, id_test INTEGER, id_software INTEGER"
            ");";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str3))
        qDebug() << "Невозможно создать таблицу 4";

    QString str4 = "CREATE TABLE column_of_logs("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "id_log INTEGER, number_column INTEGER, name_column VARCHAR(150)"
            ");";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str4))
        qDebug() << "Невозможно создать таблицу 5";

    QString str5 = "CREATE TABLE data_of_log("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "id_log INTEGER, number_column INTEGER, data VARCHAR(150)"
            ");";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str5))
        qDebug() << "Невозможно создать таблицу 6";

    QString str6 = "CREATE TABLE models_of_measurement("
            "id INTEGER PRIMARY KEY NOT NULL,"
            "name VARCHAR(150)"
            ");";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str6))
        qDebug() << "Невозможно создать таблицу 7";
}

