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




//_FOSCSEL(FNOSC_FRC)
//_FOSC(OSCIOFNC_ON & IOL1WAY_OFF)
//_FWDT(FWDTEN_OFF)


bool i = false;
void main() {

    TRISA = 0x0;
    TRISB = 0x00;
    PORTB = 0;
    PORTA = 0;

    ANSELB = 0;
    ANSELA = 0;



    PR2 = 28346;
    T2CON = 0xA020;


    IEC0bits.T2IE = 1;
    INTCON2bits.GIE = 1;

    while (1) {
        delay(10);
    }

    return 0;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0;
    //asm(" bclr IFS0, #7  ");


    if (i){
        PORTB = 0xffff;
        i = false;
    }
    else{
        PORTB = 0;
        i = true;
    }


}
//void __attribute__((interrupt, shadow, auto_psv)) _blabol(void) {
//    int i;
//    i = 5;
//}




/*
void __attribute__((interrupt, shadow, auto_psv)) _T3Interrupt(void) {

    IFS0bits.T3IF = 0; //  interrupt flag
    PORTAbits.RA3 = !PORTAbits.RA3; // Blikame s LED2  1x za 5sec
}
*/
