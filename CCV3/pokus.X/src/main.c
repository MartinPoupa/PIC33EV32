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



int napjeti = 0;
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
     SSRC = 0;
     ASAM = 1
     SSRGC = 0;
bclr ADCON1, #SAMP;
}

int main() {
      FrequencyT2(820);
      startInterrupts();
      AD1CON1 = 0x0f02;  //0000 1000 0000 0010


    while (1) {
        delay(1);
    }

    return 0;
}
/*

  */
