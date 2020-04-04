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

    //Zacne se prevod
    AD1CON1bits.SAMP = 0;

}

void __attribute__((interrupt, shadow, auto_psv)) _AD1Interrupt(void) {
    IFS0bits.AD1IF = 0;

    float voltage = adcGetVoltage(ADC1BUF0);

}

int main() {
FrequencyT2(100);
AD1CON1 = 0x8404;
IEC0bits.AD1IE = 1;

    while (1) {

    }
    return 0;
}
