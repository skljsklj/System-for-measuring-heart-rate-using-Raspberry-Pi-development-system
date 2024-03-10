#include <lcd.h>
#include "dialog.h"
#include <QApplication>

const int LCD_RS = 3;
const int LCD_EN = 14;
const int LCD_D0 = 4;
const int LCD_D1 = 12;
const int LCD_D2 = 13;
const int LCD_D3 = 6;

static int lcdHandle;

int main(int argc, char *argv[])
{

    if(wiringPiSetup() < 0){
            fprintf(stderr,"Greska pri inicijalizaciji: %s\n",strerror(errno));
            return 1;
        }

    lcdHandle = lcdInit(2, 16, 4, LCD_RS, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3, 0, 0, 0, 0);
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
