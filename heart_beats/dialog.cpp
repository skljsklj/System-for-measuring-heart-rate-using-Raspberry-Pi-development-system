#include "dialog.h"
#include "ui_dialog.h"

#define PCF_ADDRESS 0x48
#define AIN2 0x2

QT_CHARTS_USE_NAMESPACE

static int i = 1;
static int fd;
static int analogValue = 0;
static int row1 = 0;
static int row2 = 1;

const int LCD_RS = 3;
const int LCD_EN = 14;
const int LCD_D0 = 4;
const int LCD_D1 = 12;
const int LCD_D2 = 13;
const int LCD_D3 = 6;
static int lcdHandle;
static char heart[8] = {
    0b00000,    //h
    0b01010,
    0b11111,    //e
    0b11111,
    0b01110,    //a
    0b00100,
    0b00000,    //r
    0b00000
                //t
};

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Set the background color
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(50, 50, 50)); // Darker grey color
    setAutoFillBackground(true);
    setPalette(pal);

    // Create the layout
    QVBoxLayout *layout = new QVBoxLayout;

    // Create the chart
    series = new QLineSeries;
    chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("BPM");
    chart->setTitleBrush(QBrush(Qt::yellow)); // Set title color to yellow
    chart->setBackgroundBrush(QColor(50, 50, 50)); // Set chart background color

    xAxis = new QValueAxis;
    yAxis = new QValueAxis;
    xAxis->setRange(0, 10);
    yAxis->setRange(30, 100);
    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    // Set the axis label colors to yellow
    QBrush yellowBrush(Qt::yellow);
    xAxis->setLabelsBrush(yellowBrush);
    yAxis->setLabelsBrush(yellowBrush);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: grey;");
    layout->addWidget(chartView);

    QPen greenPen(Qt::green); // Create a green pen for the chart line
    series->setPen(greenPen); // Apply the green pen to the series

    // Create a spacer to push the widgets to the top
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addSpacerItem(spacer);

    // Create the LCD number display
    lcdNumber = new QLCDNumber;
    lcdNumber->setStyleSheet("background-color: grey;");
    layout->addWidget(lcdNumber);

    // Set the layout for the dialog
    setLayout(layout);

    // Other initialization code
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::readHeartRate);
    lcdHandle = lcdInit(2, 16, 4, LCD_RS, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3, 0, 0, 0, 0);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::readHeartRate()
{
    if (wiringPiSetup() == -1) exit(1);

    // Open I2C connection
    fd = wiringPiI2CSetup(PCF_ADDRESS);

    if (fd < 0) {
        // Handle I2C setup failure
        return;
    }

    // Read analog value
    wiringPiI2CWrite(fd, AIN2);
    analogValue = wiringPiI2CRead(fd) - 175;
    if(analogValue == 80)
        analogValue = 0;  //80 is default value (when there's no finger on sensor, it prints out 80)

    // Close the I2C connection
    ::close(fd);

    // LCD display
    lcdCharDef(lcdHandle, 0, reinterpret_cast<unsigned char*>(heart));
    lcdPosition(lcdHandle, 0, row1);
    lcdClear(lcdHandle);

    QString lcdText;

    if(analogValue == 0)
    {
        lcdText = "No heartbeat.";
        lcdPosition(lcdHandle, 0, row1);
        lcdPuts(lcdHandle, lcdText.toLocal8Bit().constData());
        lcdPosition(lcdHandle, 0, row2);
        lcdPuts(lcdHandle,":(");

    }
    else
    {
        lcdText = "BPM: " + QString::number(analogValue);
        lcdPosition(lcdHandle, 0, row1);
        lcdPuts(lcdHandle, lcdText.toLocal8Bit().constData());

        //Custom heart character
        lcdPosition(lcdHandle, 7, row1);
        lcdPutchar(lcdHandle, 0);

        lcdPosition(lcdHandle, 0, row2);
        lcdPuts(lcdHandle,":)");
    }

    // Display heart rate on GUI LCD
    if (analogValue == 0)
        ui->lcdNumber->setPalette(Qt::red); // Set LCD number color to red when value is 0
     else
        ui->lcdNumber->setPalette(Qt::green); // Set LCD number color to green for non-zero values

    ui->lcdNumber->display(analogValue); // Set LCD number color to green

    // Update the chart
    series->append(i, analogValue);
    if (i > 10) {
        i = 0;
        series->clear();
    }
    i++;
}

void Dialog::on_lcdNumber_overflow()
{
    QMessageBox::information(this, "Overflow", "Value has overflowed!");
    ui->lcdNumber->display(0);
}

void Dialog::on_Start_clicked()
{
    timer->start(1000); // Start the timer when the "Start" button is clicked
    series->append(0, 0);
}

void Dialog::on_End_clicked()
{
    timer->stop();
    series->clear();
    ui->lcdNumber->display(0);
    i = 1;
}

void Dialog::on_checkBox_stateChanged()
{
    if (ui->checkBox->isChecked())
    {
        row1 = 1;
        row2 = 0;
    }else {
        row1 = 0;
        row2 = 1;
    }
}
