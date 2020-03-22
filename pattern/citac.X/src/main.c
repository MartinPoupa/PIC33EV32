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


void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    digitalWrite(0, HIGH);
    delay(1000);
    digitalWrite(0, LOW);
    delay(1000);
}

int main() {
      pinMode(0, OUTPUT);
      pinAD(0, DIGITAL);
      FrequencyT2(1000); //nastavení přerušení 1000 Hz
    while (1) {
        delay(1);
    }

    return 0;
}
/*

  */
