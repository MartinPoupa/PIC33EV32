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
      pinMode(B, 0, INPUT);
      pinMode(B, 1, OUTPUT);
      pinMode(B, 2, INPUT);
      pinMode(B, 3, OUTPUT);
      pinMode(B, 4, OUTPUT);
      pinAD(B, 0, DIGITAL);
      pinAD(B, 1, DIGITAL);
      pinAD(B, 2, DIGITAL);
      pinAD(B, 3, DIGITAL);
      pinAD(B, 4, DIGITAL);
      CNPDB = 1;
      CNPUB = 4;
      digitalWrite(B, 4, 1);


      //setDA();

    while (1) {
 //       delay(1);
        digitalWrite(B, 1, digitalRead(B, 0));
        digitalWrite(B, 3, digitalRead(B, 2));
    }

    return 0;
}
/*

  */
