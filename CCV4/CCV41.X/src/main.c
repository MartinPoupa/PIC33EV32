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
    pinMode(B, 1, INPUT);

    pinAD(B, 0, DIGITAL);
    pinAD(B, 1, DIGITAL);

    pinPull(B, 0, UP);
    pinPull(B, 1, UP);

    setDA();

    while (TRUE) {
        if (digitalRead(B, 1)) {
            if (digitalRead(B, 0)) {
                DA(A, 3000);
            }
            else{
                DA(A, 2000);
            }
        }
        else{
            if (digitalRead(B, 0)) {
                DA(A, 1000);
            }
            else{
                DA(A, 0);
            }
        }
    }
    return 0;
}
/*

*/
