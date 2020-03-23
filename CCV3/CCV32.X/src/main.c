/*
* File:   main.c
* Author: Matej Kraus and Martin Poupa
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


int voltageDA = 0;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if (voltageDA >= 0x0fff) {
        voltageDA = 0;
    }
    voltageDA++;
    DA(A, voltageDA);

}


int main() {
      FrequencyT2(820);
      setDA();
      startInterrupts();
      DA(A, 0);


    while (1) {
        delay(1);
    }
      return 0;
}
