/*
* File:   main.c
* Author: Martin Poupa
*
* Created on 2. prosince 2018, 16:43
*/

#include "p33EV32GM002.h"

#include"include/mainFuncion.h"


#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)  {
      IFS0bits.T2IF = 0;
      //sendToSPI(0xffff);
}

void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)  {
      IFS0bits.SPI1IF = 0;
}

void sendToSPI(unsigned int value){
    unsigned int cteni = SPI1BUF;
    SPI1BUF = value;
}

int f = 0;

void toneT2B2(int frequency) {
    PR2 = ((CYCLE_FREQUENCY * 1000000) / 256) / frequency ;
    T2CON = 0xA030; // 256
}

/*
 *
 */
int main() {

    TRISA = 0x0;

    TRISB = 0x00;
    PORTB = 0;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB12 = 1;
    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB13 = 1;
    PORTA = 0;

    ANSELB = 0;
    ANSELA = 0;

    PR2 = 28346;
    T2CON = 0xA020;

    SPI1CON1 = 0x0520;

    SPI1CON2 = 0 ;

    SPI1STAT = 0x0000;

    IFS0bits.SPI1IF = 0;
    IFS0bits.T2IF = 0;

  /*  __builtin_write_OSCCONL(OSCCON & 0xBF);

    RPINR22 = 0x2426;


    __builtin_write_OSCCONL(OSCCON |  0x40);   */

    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIEN  = 1;

    /*  povoluji preruseni  od citace  */
    IEC0bits.T2IE = 1;
    IEC0bits.SPI1IE = 1;

    /*  globalni povoleni preruseni, tohle se musi povolit,
     * jinak nebude zadne preruseni krome TRAP   */
    INTCON2bits.GIE = 1;

    while (1) {

        PORTBbits.RB0 = 1;
        PORTBbits.RB0 = 0;
        sendToSPI(0xf800);
        delay(10);
        PORTBbits.RB0 = 1;

        delay(500);

        PORTBbits.RB0 = 0;
        sendToSPI(0xf000);
        delay(10);
        PORTBbits.RB0 = 1;
        delay(500);

    }

    return 0;
}
