/*
* File:   main.c
* Author: Martin Poupa
*
* Created on 2. prosince 2018, 16:43
*/







#include "p33EV32GM002.h"
#include "stdbool.h"

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


    TRISB = 0x00;
    PORTB = 0;

    ANSELB = 0;

    toneT2B0(1000);

    while (1) {
        delay(10);
    }
    return 0;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0;


    if (i){
        PORTBbits.RB0 = 1;
        PORTB = 0xffff;
        i = false;
    }
    else{
        PORTBbits.RB0 = 0;
        i = true;
    }
}

void toneT2B0(int frequency) {
    PR2 = (CYCLE_FREQUENCY / 256) / frequency ;
    T2CON = 0x8030; // 256


    IEC0bits.T2IE = 1;
    INTCON2bits.GIE = 1;

}
