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
int voltageDA = 0x0fff;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if (voltageDA == 0x0fff){
        voltageDA = 0;
    }
    else{
        voltageDA = 0x0fff;
    }

    DA(A, voltageDA);
    asm("btg PORTB, #0");

}

int main() {
      pinMode(0, OUTPUT);
      pinAD(0, DIGITAL);
      //FrequencyT2(35000);
      T2CON = 0x8000;
      PR2 = 70;
      IFS0bits.T2IF = 0;
      IEC0bits.T2IE = 1;
      setDA();
      startInterrupts();

      DA(A, 0x0fff);


    while (1) {
        delay(1);
    }

    return 0;
}
/*

  */
