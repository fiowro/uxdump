


#include "start_program.h"
#include "ui_start_program.h"

Start_program::Start_program(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start_program)
{

        ui->setupUi(this);

    ui->checkBoxPerson->setChecked(true);
    ui->label_measur->setVisible(true);
    ui->measurement->setVisible(true);

    ui->lineFilter->setVisible(false);
    ui->pushButtonQuery->setVisible(false);


    ui->tableTest->setRowCount(0);
    QSqlQuery queryA("SELECT id, name FROM test");
    while (queryA.next())
    {

        ui->Filter_test->addItem(queryA.value(1).toString(), queryA.value(0).toString());
        //mapTest[queryTest.value(0).toString()] = queryTest.value(1).toString();

    }
    QSqlQuery queryB("SELECT id, name FROM software");
    while (queryB.next())
    {
        ui->Filter_soft->addItem(queryB.value(1).toString(), queryB.value(0).toString());
    }

    QSqlQuery queryC("SELECT id, login FROM person");
    while (queryC.next())
    {
        ui->FIlter_person->addItem(queryC.value(1).toString(), queryC.value(0).toString());
    }
    QSqlQuery queryD("SELECT id, name FROM models_of_measurement");
    while (queryD.next())
        ui->measurement->addItem(queryD.value(1).toString(), queryD.value(0).toString());

    StartCreate();
    //CreateHistogram(ui->Filter_soft->currentData().toInt(), ui->Filter_test->currentData().toInt());

}

Start_program::~Start_program()
{
    delete ui;
}

void Start_program::on_pushButton_clicked()
{
    AddLog = new add_log();
    AddLog->show();
    connect(AddLog, SIGNAL(finished(int)), this, SLOT(StartCreate()));
    //connect(AddLog, SIGNAL(finished(int)), this, SLOT(StartCreate());
}
void Start_program::on_Filter_soft_currentTextChanged()
{
    if(!(ui->checkBoxPerson->isChecked()) && !(ui->checkBoxQuery->isChecked()))
    {
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();

        CreateHistogram(id_soft, id_test);
    }
    else if(ui->checkBoxQuery->isChecked())
    {
        ui->measurement->setVisible(false);
        ui->label_measur->setVisible(false);

        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        int i = 0;
        QString userQuery = ui->lineFilter->text();
        QSqlQuery query(userQuery);
        while(query.next())
            i++;

        if(i == 1)
        {
            int id_person = query.value(0).toInt();
            ui->measurement->setVisible(true);
            ui->label_measur->setVisible(true);
            CreateHistogramPerson(id_soft, id_test, id_person);

        }

        else
            CreateHistogram(id_soft, id_test, userQuery);
    }
    else
    {
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        int id_person = ui->FIlter_person->currentData().toInt();
        CreateHistogramPerson(id_soft, id_test, id_person);
    }

    Select_data();
}
void Start_program::on_Filter_test_currentTextChanged()
{
    if(!(ui->checkBoxPerson->isChecked()) && !(ui->checkBoxQuery->isChecked()))
    {
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();

        CreateHistogram(id_soft, id_test);
    }
    else if(ui->checkBoxQuery->isChecked())
    {


        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        int i = 0;
        QString userQuery = ui->lineFilter->text();
        QSqlQuery query(userQuery);
        while(query.next())
            i++;

        if(i == 1)
        {
            int id_person = query.value(0).toInt();
            CreateHistogramPerson(id_soft, id_test, id_person);

        }

        else

            CreateHistogram(id_soft, id_test, userQuery);
    }
    else
    {
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        int id_person = ui->FIlter_person->currentData().toInt();
        CreateHistogramPerson(id_soft, id_test, id_person);
    }

    Select_data();
}
void Start_program::CreateHistogram(int id_soft, int id_test)
{

    int min_id_person, max_id_person;
    int a =0;
    t.clear();

    QSqlQuery query(QString("SELECT id, id_person FROM logs WHERE id_test = %1 AND id_software =%2").
                    arg(id_test).arg(id_soft));

    QSqlQuery query1(QString("SELECT MIN(id_person) FROM logs WHERE id_test = %1 AND id_software =%2").
                     arg(id_test).arg(id_soft));
    while (query1.next()) {
        min_id_person = query1.value(0).toInt();
    }

    QSqlQuery query2(QString("SELECT MAX(id_person) FROM logs WHERE id_test = %1 AND id_software =%2").
                     arg(id_test).arg(id_soft));
    while (query2.next()) {
        max_id_person = query1.value(0).toInt();
    }

    while (query.next()) {

        int log_id = query.value(0).toInt();
        int qw = query.value(1).toInt();
        QSqlQuery queryColumn(QString("SELECT * FROM column_of_logs WHERE name_column = 'Time2' AND id_log = %1").arg(log_id));
        int g ;
        while(queryColumn.next())
            g = queryColumn.value(2).toInt();

        QSqlQuery queryMax(QString("SELECT MAX(data) FROM data_of_log WHERE id_log = %1 AND number_column = %2").
                           arg(query.value(0).toInt()).arg(g));
        QSqlQuery queryMin(QString("SELECT MIN(id) FROM data_of_log WHERE id_log = %1 AND number_column = %2").
                           arg(query.value(0).toInt()).arg(g));
        QTime max, min ;
        QString maxStr, minStr;
        while(queryMax.next())

            maxStr   = queryMax.value(0).toString();

        while(queryMin.next())
        {
            int id = queryMin.value(0).toInt();
            QSqlQuery queryTest(QString("SELECT data FROM data_of_log WHERE id = %1").
                               arg(id));
            while(queryTest.next())
                minStr = queryTest.value(0).toString();


        }
        max = QTime::fromString(maxStr, "h:m:s:z");
        min = QTime::fromString(minStr, "h:m:s:z");
        QTime currentTime = QTime::currentTime();
        int maxInt = abs(currentTime.secsTo(max));
        int minInt = abs(currentTime.secsTo(min));
        int res = (qMax(maxInt, minInt) - qMin(maxInt, minInt));
        int first = a++;
        t.append(QwtIntervalSample(res,first,a));
    }

    DrawHistogram("ID of person", "Time of all persons");

}
void Start_program::StartCreate()
{

    int log_id;
    QSqlQuery queryMax("SELECT MAX(id) FROM logs");
    while(queryMax.next())
        log_id = queryMax.value(0).toInt();

    QSqlQuery queryA(QString("SELECT * FROM logs WHERE id=%1").arg(log_id));
    while (queryA.next())
    {
        int id_person = queryA.value(1).toInt();
        int id_test = queryA.value(2).toInt();
        int id_soft = queryA.value(3).toInt();
        ui->FIlter_person->setEnabled(true);
        ui->measurement->setEditable(true);

        ui->Filter_soft->setCurrentIndex(id_soft - 1);
        ui->Filter_test->setCurrentIndex(id_test - 1);
        ui->FIlter_person->setCurrentIndex(id_person - 1);


    }

    Select_data();

}
void Start_program::Select_data()
{
    QMap<QString, QString> mapSoft, mapTest, mapPerson, mapColumn;

    int id_soft = ui->Filter_soft->currentData().toInt();
    int id_test = ui->Filter_test->currentData().toInt();
    int id_person = ui->FIlter_person->currentData().toInt();

    ui->tabelSoft->setRowCount(0);
   QSqlQuery querySoft(QString("SELECT * FROM software WHERE id=%1").arg(id_soft));
   while(querySoft.next())
   {
       int count = ui->tabelSoft->rowCount();
       ui->tabelSoft->setRowCount(count + 1);
       QTableWidgetItem *newItem = new QTableWidgetItem(querySoft.value(0).toString());
       ui->tabelSoft->setItem(count, 0, newItem);
       newItem = new QTableWidgetItem(querySoft.value(1).toString());
       ui->tabelSoft->setItem(count, 1, newItem);

       mapSoft[querySoft.value(0).toString()] = querySoft.value(1).toString();
   }

   //***TESTS ***//
   ui->tableTest->setRowCount(0);

   QSqlQuery queryTest(QString("SELECT * FROM test WHERE id=%1").arg(id_test));
   while(queryTest.next())
   {
       int count = ui->tableTest->rowCount();
       ui->tableTest->setRowCount(count + 1);
       QTableWidgetItem *newItem = new QTableWidgetItem(queryTest.value(0).toString());
       ui->tableTest->setItem(count, 0, newItem);
       newItem = new QTableWidgetItem(queryTest.value(1).toString());
       ui->tableTest->setItem(count, 1, newItem);
       newItem = new QTableWidgetItem(queryTest.value(2).toString());
       ui->tableTest->setItem(count, 2, newItem);

       mapTest[queryTest.value(0).toString()] = queryTest.value(1).toString();
   }

   //***MODULES***//
   ui->tableModule->setRowCount(0);

   QSqlQuery queryModule(QString("SELECT * FROM models_of_measurement"));
   while(queryModule.next())
   {
       int count = ui->tableModule->rowCount();
       ui->tableModule->setRowCount(count + 1);
       QTableWidgetItem *newItem = new QTableWidgetItem(queryModule.value(0).toString());
       ui->tableModule->setItem(count, 0, newItem);
       newItem = new QTableWidgetItem(queryModule.value(1).toString());
       ui->tableModule->setItem(count, 1, newItem);

   }


   //***PERSONS ***//
   ui->tablePerson->setRowCount(0);
   ui->tableColumn->setRowCount(0);
   ui->tableLogs->setRowCount(0);
   ui->tableData->setRowCount(0);

   QString query;
   if(!ui->checkBoxPerson->isChecked() && !ui->checkBoxQuery->isChecked())
       query = QString("SELECT * FROM person");
   else if(ui->checkBoxPerson->isChecked())
       query = QString("SELECT * FROM person WHERE id=%1").arg(id_person);
   else
   {
       query = ui->lineFilter->text();

   }

   QSqlQuery queryPerson(query);
   while(queryPerson.next())
   {
       int count = ui->tablePerson->rowCount();
       ui->tablePerson->setRowCount(count + 1);

       QTableWidgetItem *newItem = new QTableWidgetItem(queryPerson.value(0).toString());
       ui->tablePerson->setItem(count, 0, newItem);

       newItem = new QTableWidgetItem(queryPerson.value(1).toString());
       ui->tablePerson->setItem(count, 1, newItem);

       newItem = new QTableWidgetItem(queryPerson.value(2).toString());
       ui->tablePerson->setItem(count, 2, newItem);

       newItem = new QTableWidgetItem(queryPerson.value(3).toString());
       ui->tablePerson->setItem(count, 3, newItem);

       mapPerson[queryPerson.value(0).toString()] = queryPerson.value(1).toString();
       int id_person = queryPerson.value(0).toInt();
       //***LOGS***//
       QSqlQuery queryLog(QString("SELECT * FROM logs WHERE id_person=%1 AND id_test = %2 AND id_software = %3").
                          arg(id_person).arg(id_test).arg(id_soft));

       while(queryLog.next())
       {
           int count = ui->tableLogs->rowCount();
           ui->tableLogs->setRowCount(count + 1);

           QTableWidgetItem *newItem = new QTableWidgetItem(queryLog.value(0).toString());
           ui->tableLogs->setItem(count, 0, newItem);

           newItem = new QTableWidgetItem(mapPerson[queryLog.value(1).toString()]);
           ui->tableLogs->setItem(count, 1, newItem);

           newItem = new QTableWidgetItem(mapTest[queryLog.value(2).toString()]);
           ui->tableLogs->setItem(count, 2, newItem);

           newItem = new QTableWidgetItem(mapSoft[queryLog.value(3).toString()]);
           ui->tableLogs->setItem(count, 3, newItem);
           int id_log = queryLog.value(0).toInt();

           //**column_of_logs**//

           QSqlQuery queryColumn(QString("SELECT * FROM column_of_logs WHERE id_log = %1").arg(id_log));
           while(queryColumn.next())
           {
               int count = ui->tableColumn->rowCount();
               ui->tableColumn->setRowCount(count + 1);

               QTableWidgetItem *newItem = new QTableWidgetItem(queryColumn.value(0).toString());
               ui->tableColumn->setItem(count, 0, newItem);

               newItem = new QTableWidgetItem(queryColumn.value(1).toString());
               ui->tableColumn->setItem(count, 1, newItem);

               newItem = new QTableWidgetItem(queryColumn.value(2).toString());
               ui->tableColumn->setItem(count, 2, newItem);

               newItem = new QTableWidgetItem(queryColumn.value(3).toString());
               ui->tableColumn->setItem(count, 3, newItem);

               mapColumn[queryColumn.value(2).toString()] = queryColumn.value(3).toString();

           }

           //**data_of_logs**//

           QSqlQuery queryData(QString("SELECT * FROM data_of_log WHERE id_log = %1").arg(id_log));
           while(queryData.next())
           {
               int count = ui->tableData->rowCount();
               ui->tableData->setRowCount(count + 1);

               QTableWidgetItem *newItem = new QTableWidgetItem(queryData.value(0).toString());
               ui->tableData->setItem(count, 0, newItem);

               newItem = new QTableWidgetItem(queryData.value(1).toString());
               ui->tableData->setItem(count, 1, newItem);

               newItem = new QTableWidgetItem(mapColumn[queryData.value(2).toString()]);
               ui->tableData->setItem(count, 2, newItem);

               newItem = new QTableWidgetItem(queryData.value(3).toString());
               ui->tableData->setItem(count, 3, newItem);

           }

       }



   }
}
void Start_program::on_checkBoxPerson_clicked()
{
    if(ui->checkBoxPerson->isChecked())
    {
        ui->FIlter_person->setEnabled(true);
        ui->measurement->setVisible(true);
        ui->label_measur->setVisible(true);
        ui->checkBoxQuery->setChecked(false);
        ui->pushButtonQuery->setVisible(false);

        ui->lineFilter->setVisible(false);
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        int id_person = ui->FIlter_person->currentData().toInt();


        CreateHistogramPerson(id_soft, id_test, id_person);
        Select_data();

    }
    if(!(ui->checkBoxPerson->isChecked()))
    {
        ui->FIlter_person->setEnabled(false);
        ui->label_measur->setVisible(false);
        ui->measurement->setVisible(false);
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        CreateHistogram(id_soft, id_test);

    }
}
void Start_program::on_FIlter_person_currentTextChanged()
{
    if(ui->checkBoxPerson->isChecked())
    {
        int id_soft = ui->Filter_soft->currentData().toInt();
        int id_test = ui->Filter_test->currentData().toInt();
        int id_person = ui->FIlter_person->currentData().toInt();

        CreateHistogramPerson(id_soft, id_test, id_person);
    }

    Select_data();

}
void Start_program::CreateHistogramPerson(int id_soft, int id_test, int id_person)
{
    t.clear();
    int a =0;
    QList<int> timePoint;
    QList<double> MeasPoint;
    QList<QString> MeasString;
    QString columnName = "Time";
    QString timeFormat = "h:m:s";
    pointsBeats.clear();


    int id_measurement = ui->measurement->currentData().toInt();
    QString name_measurement;
    QSqlQuery queryMeasuremen(QString("SELECT * FROM models_of_measurement WHERE id = %1").arg(id_measurement)) ;
    while (queryMeasuremen.next())
        name_measurement = queryMeasuremen.value(1).toString();

    if(name_measurement == "Meditation" || name_measurement == "Attention")
     {
        columnName = "Time2";
        timeFormat = "h:m:s:z";
    }


    QSqlQuery query(QString("SELECT id FROM logs WHERE id_test = %1 AND id_software =%2 AND id_person = %3").
                    arg(id_test).arg(id_soft).arg(id_person));

    while (query.next()) {

        int log_id = query.value(0).toInt();

        QSqlQuery queryColumnTime(QString("SELECT * FROM column_of_logs WHERE name_column = '%1' AND id_log = %2").arg(columnName).arg(log_id));
        int g ;
        while(queryColumnTime.next())
            g = queryColumnTime.value(2).toInt();


        QSqlQuery queryTime(QString("SELECT data FROM data_of_log WHERE id_log = %1 AND number_column = %2").
                            arg(query.value(0).toInt()).arg(g));
        QTime time;
        QString TimeStr;
        while(queryTime.next())
        {
            TimeStr = queryTime.value(0).toString();

            time = QTime::fromString(TimeStr, timeFormat);
            QTime currentTime = QTime::currentTime();
            timePoint.append(abs(currentTime.secsTo(time)));

        }
        
        QSqlQuery queryColumnBeats(QString("SELECT * FROM column_of_logs WHERE name_column = '%1' AND id_log = %2").arg(name_measurement).arg(log_id));
        
        while(queryColumnBeats.next())
            g = queryColumnBeats.value(2).toInt();


        QSqlQuery queryBeats(QString("SELECT data FROM data_of_log WHERE id_log = %1 AND number_column = %2").
                            arg(query.value(0).toInt()).arg(g));
        while(queryBeats.next())
        {

            MeasPoint.append(queryBeats.value(0).toDouble());
            MeasString.append(queryBeats.value(0).toString());
        }
    }

   for(int i = 0; i<MeasPoint.length(); i++)
   {
       if(name_measurement == "Meditation" || name_measurement == "Attention" || name_measurement == "Value GSR")
       {
           if(MeasPoint[i]>0 && timePoint[i]>0)
               pointsBeats<<QPointF(timePoint[i], MeasPoint[i]);
       }
       else
       {
           if(name_measurement == "Beats per minute" &&
               MeasPoint[i]>= 50 && MeasPoint[i] <= 130)
                   pointsBeats<<QPointF(timePoint[i], MeasPoint[i]);
           else
           {
               if(name_measurement == "PTT" &&
                       MeasPoint[i]>= 10 && MeasPoint[i] <= 100)
                   pointsBeats<<QPointF(timePoint[i], MeasPoint[i]);

           }
       }


   }
    DrawCurve(name_measurement);

}



void Start_program::on_checkBoxQuery_clicked()
{
    ui->lineFilter->setVisible(true);
    ui->pushButtonQuery->setVisible(true);
    if(ui->checkBoxPerson->isChecked())
    {
        ui->checkBoxPerson->setChecked(false);
        ui->FIlter_person->setEnabled(false);
        ui->checkBoxQuery->setChecked(true);
        ui->measurement->setVisible(false);
        ui->label_measur->setVisible(false);

    }
    else
    {

        if(!(ui->checkBoxQuery->isChecked()))
        {

            ui->lineFilter->setVisible(false);
           ui->pushButtonQuery->setVisible(false);

        }
    }

    Select_data();
}
void Start_program::CreateHistogram(int id_soft, int id_test, QString userQuery)
{
    int a = 0;
    t.clear();
    QSqlQuery query1(userQuery);

    while(query1.next())
    {

        int id_person = query1.value(0).toInt();
        QSqlQuery query(QString("SELECT id FROM logs WHERE id_test = %1 AND id_software =%2 AND id_person = %3").
                        arg(id_test).arg(id_soft).arg(id_person));
        while (query.next()) {

            int log_id = query.value(0).toInt();

            QSqlQuery queryColumn(QString("SELECT * FROM column_of_logs WHERE name_column = 'Time' AND id_log = %1").arg(log_id));
            int numberColumn ;
            while(queryColumn.next())
                numberColumn= queryColumn.value(2).toInt();


            QSqlQuery queryMax(QString("SELECT MAX(data) FROM data_of_log WHERE id_log = %1 AND number_column = %2").
                               arg(query.value(0).toInt()).arg(numberColumn));
            QTime max, min ;
            QString maxStr, minStr;
            while(queryMax.next())

                maxStr   = queryMax.value(0).toString();


            QSqlQuery queryMin(QString("SELECT MIN(data) FROM data_of_log WHERE id_log = %1 AND number_column = %2").
                               arg(query.value(0).toInt()).arg(numberColumn));

            while(queryMin.next())
                minStr = queryMin.value(0).toString();
            max = QTime::fromString(maxStr, "h:m:s");
            min = QTime::fromString(minStr, "h:m:s");
            QTime currentTime = QTime::currentTime();
            int maxInt = abs(currentTime.secsTo(max));
            int minInt = abs(currentTime.secsTo(min));
            int res = maxInt - minInt;

            int first = a++;

            t.append(QwtIntervalSample(res,first,a));
        }


    }

    ui->myPlot_2->detachItems();
    histogram = new QwtPlotHistogram();
    histogram->setStyle(QwtPlotHistogram::Columns);
    histogram->setBrush(Qt::blue);
    histogram->setSamples(t);
    histogram->attach(ui->myPlot_2);
    ui->myPlot_2->setAxisTitle(QwtPlot::yLeft, "Duration of test, s");
    ui->myPlot_2->setAxisTitle(QwtPlot::xBottom, "ID of person");
    ui->myPlot_2->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    QwtPlotGrid *grid = new QwtPlotGrid(); //
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach( ui->myPlot_2 ); // добавить сетку к полю графика

    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(ui->myPlot_2->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);

    QwtPlotPanner *d_panner = new QwtPlotPanner( ui->myPlot_2->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
     ui->myPlot_2->replot();

}
void Start_program::on_pushButtonQuery_clicked()
{
    ui->myPlot_2->detachItems();

    int id_soft = ui->Filter_soft->currentData().toInt();
    int id_test = ui->Filter_test->currentData().toInt();
    int i = 0;
    QString userQuery = ui->lineFilter->text();
    QSqlQuery query(userQuery);
    while(query.next())
        i++;

    if(i == 1)
    {
        int id_person = query.value(0).toInt();
        CreateHistogramPerson(id_soft, id_test, id_person);

    }

    else
        CreateHistogram(id_soft, id_test, userQuery);
    Select_data();
}
void Start_program::on_tabWidget_currentChanged(int index)
{
    ui->FIlter_person->setEnabled(false);
   // ui->lineFilter->setEnabled(false);
    ui->Filter_soft->setEnabled(true);
    ui->Filter_test->setEnabled(true);
    if(ui->checkBoxPerson->isChecked())
        ui->FIlter_person->setEnabled(true);
    if(ui->checkBoxQuery->isChecked())
    {
        ui->lineFilter->setEnabled(true);
        ui->pushButtonQuery->setEnabled(true);
    }
    if(index == 1 || index == 2)
    {
        ui->Filter_soft->setEnabled(true);
        ui->Filter_test->setEnabled(true);
        ui->FIlter_person->setEnabled(false);
        ui->lineFilter->setEnabled(false);
        ui->pushButtonQuery->setEnabled(false);
    }
    if(index == 3)
    {
        ui->Filter_soft->setEnabled(false);
        ui->Filter_test->setEnabled(false);
        if(ui->checkBoxPerson->isChecked())
            ui->FIlter_person->setEnabled(true);
        if(ui->checkBoxQuery->isChecked())
        {
            ui->lineFilter->setEnabled(true);
            ui->pushButtonQuery->setEnabled(true);
        }
    }
}
void Start_program::DrawHistogram(QString XTitle, QString HistogramTitle)
{
    ui->myPlot_2->detachItems();
    histogram = new QwtPlotHistogram();
    histogram->setStyle(QwtPlotHistogram::Columns);
    histogram->setBrush(Qt::blue);
    histogram->setSamples(t);
    histogram->attach(ui->myPlot_2);
    ui->myPlot_2->setTitle(HistogramTitle);
    ui->myPlot_2->setAxisTitle(QwtPlot::yLeft, "Duration of test, s");
    ui->myPlot_2->setAxisTitle(QwtPlot::xBottom, XTitle);
    ui->myPlot_2->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    QwtPlotGrid *grid = new QwtPlotGrid(); //
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach( ui->myPlot_2 ); // добавить сетку к полю графика

    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(ui->myPlot_2->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);

    QwtPlotPanner *d_panner = new QwtPlotPanner( ui->myPlot_2->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );

    ui->myPlot_2->replot();
}

void Start_program::DrawCurve(QString name_measurement)
{
        ui->myPlot_2->detachItems();

        ui->myPlot_2->setTitle(name_measurement);
        ui->myPlot_2->setAxisTitle(QwtPlot::yLeft, "Value");
        ui->myPlot_2->setAxisTitle(QwtPlot::xBottom, "Time stamp");
        ui->myPlot_2->setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

        curv2 = new QwtPlotCurve();
        curv2->setStyle(QwtPlotCurve::Lines);
        curv2->setPen(Qt::red, 2);
        curv2->setRenderHint( QwtPlotItem::RenderAntialiased, true ); // сглаживание
        curv2->setSamples(pointsBeats);
        curv2->attach(ui->myPlot_2);

        QwtPlotGrid *grid = new QwtPlotGrid(); //
        grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
        grid->attach( ui->myPlot_2 ); // добавить сетку к полю графика

        QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(ui->myPlot_2->canvas());
        // клавиша, активирующая приближение/удаление
        magnifier->setMouseButton(Qt::MidButton);

        QwtPlotPanner *d_panner = new QwtPlotPanner( ui->myPlot_2->canvas() );
        // клавиша, активирующая перемещение
        d_panner->setMouseButton( Qt::RightButton );

        ui->myPlot_2->replot();

}

void Start_program::on_measurement_currentTextChanged(const QString &arg1)
{

    CreateHistogramPerson(ui->Filter_soft->currentData().toInt(),
                          ui->Filter_test->currentData().toInt(),
                          ui->FIlter_person->currentData().toInt());

}


