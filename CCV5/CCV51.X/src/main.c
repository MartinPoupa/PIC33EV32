/*
* File:   main.c
* Author: Martin Poupa
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    int voltage = analogRead(A, 0);
    voltage = voltage & 3840;
    int i;
    for( i = 0; i < 8; i++) {
        voltage = voltage / 2;
    }
    PORTB = voltage;
}

int main() {
    pinMode(A, 0, INPUT);
    pinAD(A, 0, ANALOG);
    int j;
    for( j = 0; j < 8; j++) {
        pinMode(B, j, OUTPUT);
        pinAD(B, j, DIGITAL);
    }

    startInterrupts();
    FrequencyT2(1000);
    while (1) {
        delay(1);
    }
    return 0;
}
