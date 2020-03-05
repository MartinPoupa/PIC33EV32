/*
* File:   main.c
* Author: Martin Poupa
*
*/







#include "p33EV32GM002.h"

#include"include/mainFuncion.h"


#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

#define C2 523
#define D2 587
#define E2 659
#define F2 698
#define G2 784
#define A2 880
#define B2 988
#define C3 1047



//_FOSCSEL(FNOSC_FRC)
//_FOSC(OSCIOFNC_ON & IOL1WAY_OFF)
//_FWDT(FWDTEN_OFF)




int f = 0;

void toneT2B2(int frequency) {
    PR2 = ((CYCLE_FREQUENCY * 1000000) / 256) / frequency ;
    T2CON = 0xA030; // 256
    IEC0bits.T2IE = 1;
}


void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0;


    if (f == 0){
        PORTBbits.RB2 = 1;
        f = 1;
    }
    else{
        PORTBbits.RB2 = 0;
        f = 0;
    }
}


void main() {
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    ANSELB = 0;
    digitalWrite(0, HIGH);
    digitalWrite(3, HIGH);

    INTCON2bits.GIE = 1;

    while (1) {
        delay(500);
    }
}
