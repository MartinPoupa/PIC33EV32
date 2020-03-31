/*
* File:   main.c
* Author: Matej Kraus and Martin Poupa
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"
#include "include/note.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

#define TAKT 200

int main() {


    setDA();
    FrequencyT2(500);
    DA(A, 0);
    startInterrupts();



    while (1) {
        note( C1 ,TAKT * 3);

        note( A0 ,TAKT * 3);

        note( F0 ,TAKT * 3);

        note( C0 ,TAKT * 3);

        note( D0 ,TAKT);
        note( E0 ,TAKT);
        note( F0 ,TAKT);

        note( D0 ,TAKT * 2);
        note( F0 ,TAKT);

        note( C0 ,TAKT * 3);

        note( C0 ,TAKT * 3);

        note( D0 ,TAKT * 3);

        note( BB0 ,TAKT * 3);

        note( A0 ,TAKT * 3);

        note( F0 ,TAKT * 3);

        note( D0 ,TAKT);
        note( E0 ,TAKT);
        note( F0 ,TAKT);

        note( G0 ,TAKT * 2);
        note( C1 ,TAKT);

        note( G0 ,TAKT * 3);

        note( G0 ,TAKT * 2);
        note( A0 ,TAKT);

        note( BB0 ,TAKT);
        note( A0 ,TAKT);
        note( G0 ,TAKT);

        stopInterrupts();
        delay (10000);
        startInterrupts();

    }
    return 0;
}
