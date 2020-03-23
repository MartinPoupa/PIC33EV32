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



int main() {
      setDA();                    //Nastaveni DA prevodniku

    while (1) {
        delay(2000);
        DA(A, 1000);
        delay(2000);
        DA(A, 2970);
    }
      return 0;
}
