#include "p33EV32GM002.h"


#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


int i;

int main() {


    i = 0;

    TRISA = 0x0;
    TRISB = 0 ;
    ANSELA = 0;
    ANSELB = 0;



    PORTB = 0x2000;


    __builtin_write_OSCCONL(OSCCON & 0xBF)    ;


    RPOR1  =  0x0800 ;   // nahore   pin 14
    RPOR2  =  0x0009 ;  // dole      pin 15

    RPINR22 =  0x2600;   //   nahore

    __builtin_write_OSCCONL(OSCCON |  0x40)    ;



    //   zacina SPI


    i = SPI2BUF;
    i = SPI2BUF;
    i = SPI2BUF;
    i = SPI2BUF;
    i = 0 ;

    SPI2STAT = 0;
    SPI2CON1 = 0x053b ;
    SPI2CON2 = 0 ;

    SPI2STATbits.SPIROV = 0 ;

    SPI2STATbits.SPIEN = 1 ;


    PR2 = 28346;
    T2CON = 0xA030;


    IEC0bits.T2IE = 1;
    IEC2bits.SPI2IE = 1 ;

    INTCON2bits.GIE = 1;

    while (1) {

        asm(" btg PORTA, #0 ");
        asm(" btg PORTA, #1 ");
        asm(" btg PORTA, #2 ");

    }

    return 0;
}


void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    int j ;
    IFS0bits.T2IF = 0;
    PORTBbits.RB13 = 0 ;
    j = SPI2BUF;
    i = ! i ;
    if (i){
        SPI2BUF = 0x1a00;
    }
    else {
        SPI2BUF = 0x1400;
    }
                                                        //  0001 0100 0000 0000    1/4  maxima
}


void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void) {
    IFS2bits.SPI2IF  = 0 ;
    PORTBbits.RB13 = 1 ;

     asm(" btg PORTB, #0 ");

}
