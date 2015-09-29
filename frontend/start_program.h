#ifndef START_PROGRAM_H
#define START_PROGRAM_H

#include<qwt.h>
#include <QMainWindow>
#include <qwt_plot_histogram.h>
#include <qwt_plot_curve.h>
#include "add_log.h"
#include "start_program.h"
#include "ui_start_program.h"

#include <QMessageBox>

#include <QtSql>
#include <QtSql/qsqlquery.h>
#include<qstring.h>
#include <string>
#include <string.h>
#include <qstring.h>
#include <math.h>

#include <qwt_plot_histogram.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_legenditem.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>

namespace Ui {
class Start_program;
}

class Start_program : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start_program(QWidget *parent = 0);
    ~Start_program();

private slots:
    void on_pushButton_clicked();

    void CreateHistogram(int id_soft, int id_test, QString userQuery);
    void CreateHistogram(int id_soft, int id_test);
    void CreateHistogramPerson(int id_soft, int id_test, int id_person);
    void StartCreate();
    void on_Filter_soft_currentTextChanged();
    void on_Filter_test_currentTextChanged();
    void on_FIlter_person_currentTextChanged();

    void on_checkBoxQuery_clicked();
    void on_checkBoxPerson_clicked();
    void  on_pushButtonQuery_clicked();
    void Select_data();
    void on_tabWidget_currentChanged(int index);
    void DrawHistogram(QString XTitle,  QString HistogramTitle);
    void DrawCurve(QString name_measurement);

    void on_measurement_currentTextChanged(const QString &arg1);

private:

    Ui::Start_program *ui;
    add_log *AddLog;
    QVector<QwtIntervalSample> t;
    QwtPlotHistogram *histogram;
    QwtPlotCurve *curv2;

    QPolygonF pointsBeats;

};

#endif // START_PROGRAM_H
