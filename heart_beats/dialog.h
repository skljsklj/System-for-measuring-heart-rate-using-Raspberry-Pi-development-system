#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QMenu>
#include <QThread>
#include <QCoreApplication>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <lcd.h>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void readHeartRate();
    void on_lcdNumber_overflow();
    void on_Start_clicked();
    void on_End_clicked();
    void on_checkBox_stateChanged();

private:
    Ui::Dialog *ui;
    QLCDNumber *lcdNumber;
    QLineSeries *series;
    QChart *chart;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QChartView *chartView;
    QTimer *timer;
};

#endif // DIALOG_H
