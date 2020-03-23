/*
* File:   main.c
* Author: Martin Poupa
*
*/

#include "p33EV32GM002.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

#define  OSCILACION_FREQUENCY 7.37
#define  CYCLE_FREQUENCY (OSCILACION_FREQUENCY / 2)

#define OUTPUT 0
#define INPUT 1

#define A 1
#define B 0

#define LOW 0
#define HIGH 1

#define DIGITAL 0
#define ANALOG 1

int f = 0;

void delay(int);
void pinMode(int, int);
void pinAD(int, int);
void digitalWrite(int, int);

void FrequencyT2(int divisor,int frequency) {
    if(divisor == 1){
        T2CON = 0x8000; // 1
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(divisor == 8){
        T2CON = 0x8010; // 8
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(divisor == 64){
        T2CON = 0x8020; // 64
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(divisor == 256){
        T2CON = 0x8030; // 256
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }

}




void startInterrupts(){
    INTCON2bits.GIE = 1;
}

void setDA (){
    //pin set
    /*
    TRISBbits.5 = 0 ;//  14 sdo
    TRISBbits.6 = 0;  //  15 sck
    TRISBbits.13 = 0; // 24 cs

    ANSELBbits.5 = 0; // 24 cs
    ANSELBbits.6 = 0;
    ANSELBbits.13 = 0;
*/
     TRISB = 0;
     ANSELB = 0;

    PORTBbits.RB5 = 0;
    PORTBbits.RB6 = 0;
    PORTBbits.RB13 = 1;

    //PPS
    __builtin_write_OSCCONL(OSCCON & 0xBF);

    RPOR1 = 0x0800; //  14 sdo
    RPOR2 = 0x0090; //  15 sck in

    RPINR22 = 0x2600; // 15 sck out

    __builtin_write_OSCCONL(OSCCON |  0x40);

    //SPI
    int cteni = SPI2BUF;
    cteni = SPI2BUF;
    cteni = SPI2BUF;
    cteni = SPI2BUF;

    SPI2STAT = 0;
    SPI2CON1 = 0x053b;
    SPI2CON2 = 0 ;
    SPI2STATbits.SPIEN = 1;
    SPI2STATbits.SPIROV = 0;

    //SPI interapt
    IFS2bits.SPI2IF = 0;
    IEC2bits.SPI2IE = 1;
}


void DA (int convertor, int voltage){
    if(voltage < 0x1000 && voltage >= 0){
        PORTBbits.RB13 = 0;
        int cteni = SPI2BUF ;
        SPI2BUF = (voltage + (0x8000 * convertor) + 0x1000);
    }
}


void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void)  {
      IFS2bits.SPI2IF = 0;
      PORTBbits.RB13 = 1;
}


///////////////////////////////////////////////////////////////////////////

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0;
    PORTBbits.RB13 = 0;
    int cteni = SPI2BUF;
    SPI2BUF = 0x9FA5;

}

int main() {

      setDA();
      FrequencyT2(64,10000);
      startInterrupts();

    while (1) {
        delay(1);
    }

    return 0;
}
/*

  */
