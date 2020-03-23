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


//int state = 0;
//int voltageDA = 0;

/*void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0;
    if (voltageDA >= 0x0fff) {
        digitalWrite(0, LOW );
        state = 1;
        voltageDA = 0x0fff;
    }
    if (voltageDA <= 0) {
        digitalWrite(0, HIGH );
        state = 0;
        voltageDA = 0;
    }

    if (state == 0) {
        DA(A, voltageDA);

        voltageDA = voltageDA + 334;
    }
    else{
        DA(A, voltageDA);
        voltageDA = voltageDA - 334;
    }



}*/

void main() {
      TRISB=0;
      ANSELB=0;
      FrequencyT2(25000);         //Nastaveni frekvence preruseni od T2
      setDA();                    //Nastaveni DA prevodniku
      startInterrupts();          //Generalni povoleni preruseni

      DA(A, 0x0fff);              //A=ktery prevodnik; 0x0fff=jake cislo posilame


    while (1) {
        //
        delay(1000);
        DA(A, 910);

        delay(1000);
        DA(A, 2730);
    }
}
