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
        note( C2 ,TAKT * 3);

        note( A1 ,TAKT * 3);

        note( F1 ,TAKT * 3);

        note( C1 ,TAKT * 3);

        note( D1 ,TAKT);
        note( E1 ,TAKT);
        note( F1 ,TAKT);

        note( D1 ,TAKT * 2);
        note( F1 ,TAKT);

        note( C1 ,TAKT * 3);

        note( C1 ,TAKT * 3);

        note( D1 ,TAKT * 3);

        note( BB1 ,TAKT * 3);

        note( A1 ,TAKT * 3);

        note( F1 ,TAKT * 3); 

        note( D1 ,TAKT);
        note( E1 ,TAKT);
        note( F1 ,TAKT);

        note( G1 ,TAKT * 2);
        note( B1 ,TAKT);

        note( G1 ,TAKT * 3);

        note( G1 ,TAKT * 2);
        note( A1 ,TAKT);

        note( BB1 ,TAKT);
        note( A1 ,TAKT);
        note( G1 ,TAKT);

        delay(10000);

    }
    return 0;
}
