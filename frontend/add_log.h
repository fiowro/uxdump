#ifndef ADD_LOG_H
#define ADD_LOG_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>

#include "databasework.h"
#include <QMessageBox>

#include <QtSql>
#include <QtSql/qsqlquery.h>
#include<qstring.h>
#include <string>
#include <string.h>
#include<QDir>
#include <QTime>


namespace Ui {
class add_log;
}

class add_log : public QDialog
{
    Q_OBJECT

public:
    explicit add_log(QWidget *parent = 0);
    ~add_log();

private slots:
    void on_download_clicked();
    void checkString(QString &temp, QChar character = 0, int column = 0, int id_log = 0);
    void checkString2(QString &temp, QChar character = 0, int column = 0, int id_log = 0);
    void readData();
    int AddPerson(int id_person);
    int AddLog(int id_person);
    void CSVReader(int id_log, QString fileName = "");

    void on_startTest_clicked();

private:
    Ui::add_log *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QStandardItemModel *model1;
    QList<QStandardItem*> standardItemList;
    QList<QStandardItem*> standardItemList1;

    QString login;
    QChar sex;
    int age;
    int test;
    int soft;

};

#endif // ADD_LOG_H
