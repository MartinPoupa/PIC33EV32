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
int voltageDA = 0x9fff;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    //DA(voltageDA);
    asm("btg PORTB, #13");

}

int main() {
      pinMode(0, OUTPUT);
      pinAD(0, DIGITAL);
      FrequencyT2(35000);
      setDA();
      startInterrupts();

      DA(0x0fff);


    while (1) {
        delay(1);
    }

    return 0;
}
/*

  */
