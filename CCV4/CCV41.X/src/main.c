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

int state = 0;
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if (state == 0) {
        state = 1;
        digitalWrite(0, 1);
    }
    else{
        state = 0;
        digitalWrite(0, 0);
    }
}



int main() {
      pinMode(0, OUTPUT);
      pinMode(1, INPUT);
      pinMode(2, OUTPUT);
      pinAD(0, DIGITAL);
      pinAD(1, DIGITAL);
      pinAD(2, DIGITAL);
      FrequencyT2(1);
      startInterrupts();


      //setDA();

    while (1) {
 //       delay(1);
        int a = digitalRead(1)
        digitalWrite(2,a);
    }

    return 0;
}
/*

  */
