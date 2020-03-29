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
      pinMode(B, 0, OUTPUT);
      pinMode(B, 1, INPUT);
      pinMode(B, 2, OUTPUT);
      pinMode(B, 3, OUTPUT);
      pinAD(B, 0, DIGITAL);
      pinAD(B, 1, DIGITAL);
      pinAD(B, 2, DIGITAL);
      pinAD(B, 3, DIGITAL);

      digitalWrite(B, 3, 1);
      int a = 0;


      //setDA();

    while (1) {
 //       delay(1);
        int a = digitalRead(B, 1);
        digitalWrite(B, 0, a);
        digitalWrite(B, 2, digitalRead(B, 1));
    }

    return 0;
}
/*

  */
