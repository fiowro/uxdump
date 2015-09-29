#include "add_log.h"
#include "ui_add_log.h"

using namespace std;

add_log::add_log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_log)
{
    ui->setupUi(this);


    QSqlQuery queryA("SELECT id, name FROM test");
    while (queryA.next())
    {
        ui->test_id->addItem(queryA.value(1).toString(), queryA.value(0).toString());
    }

    QSqlQuery queryB("SELECT id, name FROM software");
    while (queryB.next())
    {
        ui->software_id->addItem(queryB.value(1).toString(), queryB.value(0).toString());
    }
}

add_log::~add_log()
{
    delete ui;
}

void add_log::on_download_clicked()
{
    readData();
    int id_person = AddPerson(1);
    int id_log = AddLog(id_person);
    CSVReader(id_log);
}

void add_log::checkString(QString &temp, QChar character, int column, int id_log)
{

    QSqlQuery query1("SELECT max(id) FROM data_of_log");
    query1.next();
    int id_data_of_log = query1.value(0).toInt();
    id_data_of_log++;

    QSqlQuery a_query;
    QString str;
        str = QString("INSERT INTO data_of_log(id, id_log, number_column, data)"
                      " VALUES (%1, %2, %3, '%4')").arg(id_data_of_log).arg(id_log).arg(column).arg(temp);
   qDebug() << str;

    bool b = a_query.exec(str);
    if (!b) {
        QMessageBox::warning(this, "Добавление записи",
                             "В данный момент мы не можем добавить запись, попробуйте позже.");
    } else {
        this->close();
    }

    temp.clear();
}


void add_log::checkString2(QString &temp, QChar character, int column, int id_log)
{
    QSqlQuery query1("SELECT max(id) FROM column_of_logs");
    query1.next();
    int id_column_of_logs = query1.value(0).toInt();
    id_column_of_logs++;
   QString name = temp;
    QSqlQuery a_query;
    QString str;
        str = QString("INSERT INTO column_of_logs(id, id_log, number_column, name_column)"
                      " VALUES (%1, %2, %3, '%4')").arg(id_column_of_logs).arg(id_log).arg(column).arg(name);
   qDebug() << str;

    bool b = a_query.exec(str);
    if (!b) {
        QMessageBox::warning(this, "Добавление записи",
                             "В данный момент мы не можем добавить запись, попробуйте позже.");
    } else {
        this->close();
    }
    temp.clear();
}

int add_log::AddPerson(int id_person)
{
    QSqlQuery query("SELECT max(id) FROM person");
    query.next();
    id_person = query.value(0).toInt();
    id_person++;

    QSqlQuery a_query;
    QString str;
        str = QString("INSERT INTO person(id, login, sex, age)"
                      " VALUES (%1, '%2', '%3', %4)").arg(id_person).arg(login).arg(sex).arg(age);
   qDebug() << str;

    bool b = a_query.exec(str);
    if (!b) {
        QMessageBox::warning(this, "Добавление записи",
                             "В данный момент мы не можем добавить запись, попробуйте позже.");
    } else {
        this->close();
        return id_person;
    }
}

int add_log::AddLog(int id_person)
{
    QSqlQuery query1("SELECT max(id) FROM logs");
    query1.next();
    int id_log = query1.value(0).toInt();
    id_log++;

    QSqlQuery c_query;
    QString str1;
        str1 = QString("INSERT INTO logs(id, id_person, id_test, id_software) "
                       "VALUES (%1, %2, %3, %4)").arg(id_log).arg(id_person).arg(test).arg(soft);
   qDebug() << str1;

   bool d = c_query.exec(str1);
   if (!d) {
       QMessageBox::warning(this, "Добавление записи",
                            "В данный момент мы не можем добавить запись, попробуйте позже.");
   } else {
       this->close();
       return id_log;
   }
}

void add_log::CSVReader(int id_log, QString fileName)
{

    QSqlQuery query;
    QString str = "BEGIN";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query.exec(str))
        qDebug() << "Не бегин";

    model = new QStandardItemModel(this);
    model1 = new QStandardItemModel(this);

    if(fileName == "")
        fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)

        QString temp;

        QChar character;
        QTextStream textStream(&data);
        int a=0;
        int column = 1;
        while (!textStream.atEnd())
        {
            textStream >> character;
            if (a==0)
            {
                if (character == ',')
                {
                    checkString2(temp, character, column, id_log);
                    column++;
                }
                else
                    if (character == '\n')
                    {
                        checkString2(temp, character, column, id_log);
                        column = 1;
                        a++;
                    }
                    else
                        if (textStream.atEnd())
                        {
                            temp.append(character);
                            checkString2(temp, character, column, id_log);
                            column++;
                        }
                        else
                        {
                            temp.append(character);
                        }
            }

            else
            {
                if (character == ',')
                {
                    checkString(temp, character, column, id_log);
                    column++;
                }
                else
                    if (character == '\n')
                    {
                        checkString(temp, character, column, id_log);
                        column = 1;
                    }
                    else
                        if (textStream.atEnd())
                        {
                            temp.append(character);
                            checkString(temp, character, column, id_log);
                            column++;
                        }
                        else
                        {
                            temp.append(character);
                        }
            }
        }

    }
    QSqlQuery query1;
    QString str1 = "COMMIT";

    //***ПРОВЕРКА СОЗДАНИЯ***
    if(!query1.exec(str1))
        qDebug() << "Не коммит";

}



void add_log::readData()
{
    login = ui->login->text();
    test = ui->test_id->currentData().toInt();
    soft = ui->software_id->currentData().toInt();

    if(ui->sex->text() == "F" ||ui->sex->text() =="f")
        sex = 'F';
    else if(ui->sex->text() == "M" ||ui->sex->text() =="m")
            sex = 'M';
    else
    {
        QMessageBox::warning(this, "Добавление записи",
                                 "Некорректное заполнение поля sex");
    }

    if(ui->age->text().toInt() < 16 || ui->age->text().toInt() > 90)
    {
        QMessageBox::warning(this, "Добавление записи",
                             "Некорректное заполнение поля age, возраст должен быть от 16 до 90");
    }

    else
        age = ui->age->text().toInt();
}

void add_log::on_startTest_clicked()
{

    QString software;
    QString testDir;

    readData();
     QSqlQuery queryTest(QString("SELECT id, name FROM test WHERE id=%1").arg(test));
     while (queryTest.next())
     {
         if(queryTest.value(1).toString() == "Text Write")
             testDir = "/home/asya/ver3/Debug/TestTextWriter";

     }

     QSqlQuery querySoft(QString("SELECT id, name FROM software WHERE id=%1").arg(soft));
     while (querySoft.next())
     {
         if(querySoft.value(1).toString() == "LibreOffice")
             software = "libreoffice";
         if(querySoft.value(1).toString() == "Calligra Suite")
             software = "calligrawords";

     }

     QStringList myList; // Список файлов этой папки
     QDir myDirectory = QDir(testDir); // Текущая папка
     QStringList nameFilter;
     nameFilter<<"*.doc";
     myList = myDirectory.entryList(nameFilter, QDir::Files); // Получить список


    QProcess *test = new QProcess(this);
    QProcess *vec = new QProcess(this);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    vec->start("./zaglushka");
    while(vec->isOpen())
    {

        test->start(software + " " +testDir + "/" + myList[qrand() % myList.length()]);

    if(!test->waitForFinished(10000)) //must be 180k
        vec->close();
    }

   test->finished(0, QProcess::NormalExit);
    test->kill();
    vec->kill();

       int id_person = AddPerson(1);
       int id_log = AddLog(id_person);
       QString fileName = "/home/asya/ver3/Debug/resultTest/Test.csv";
       CSVReader(id_log, fileName);

}




