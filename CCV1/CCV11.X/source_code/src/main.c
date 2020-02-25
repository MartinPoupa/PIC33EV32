/*
* File:   main.c
* Author: Martin Poupa
*
* Created on 2. prosince 2018, 16:43
*/



#include "p33EV32GM002.h"

#include"include/mainFuncion.h"




#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut




void  main() {
    int a;

    a = pokus(a); // zdar

    asm(" nop " );
    asm(" nop " );
    asm(" nop " );
    asm(" nop " );
    asm(" nop " );

    while(1) {

        asm(" nop " );
        asm(" nop " );
        asm(" nop " );
        asm(" nop " );

    }
}
