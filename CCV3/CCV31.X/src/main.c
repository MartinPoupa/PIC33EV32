/*
* File:   main.c
* Author: Matej Kraus
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut




void main() {
      TRISB=0;
      ANSELB=0;
      
      setDA();
      startInterrupts();

      DA(A, 0x0fff);


    while (1) {

        delay(1000);
        DA(A, 910);

        delay(1000);
        DA(A, 2730);
    }
}
