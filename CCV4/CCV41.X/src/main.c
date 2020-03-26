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





int main() {
      pinMode(0, OUTPUT);
      pinMode(1, INPUT);
      pinMode(2, OUTPUT);
      pinAD(0, DIGITAL);
      pinAD(1, DIGITAL);
      pinAD(2, DIGITAL);


      //setDA();

    while (1) {
 //       delay(1);
        int a = digitalRead(1);
        digitalWrite(0,a);
        digitalWrite(2,PORTBbits.RB1);
    }

    return 0;
}
/*

  */
