/*
* File:   main.c
* Author: Martin Poupa
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config IESO  = OFF     //  Start up device with user selected oscillator source , u nas FRC
#pragma config  FCKSM  =   CSECMD  //  Clock Switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config POSCMD = NONE	//Primary Oscillator disabled
#pragma config OSCIOFNC = OFF   //OSC2 OSC2 is clock output   RA3   pin 10
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut



int main() {
    pinMode(B, 0, OUTPUT);
    pinAD(B, 0, DIGITAL);
    pinMode(B, 1, OUTPUT);
    pinAD(B, 1, DIGITAL);
    pinMode(B, 2, OUTPUT);
    pinAD(B, 2, DIGITAL);
    pinMode(B, 3, OUTPUT);
    pinAD(B, 3, DIGITAL);


   CLKDIVbits.FRCDIV =  0;
   PLLFBD=79;
   CLKDIVbits.PLLPOST=1;
   CLKDIVbits.PLLPRE=1;

   digitalWrite(B, 0, HIGH);

   __builtin_write_OSCCONH(0x01);
   __builtin_write_OSCCONL(OSCCON | 0x01);
   digitalWrite(B, 1, HIGH);


while (OSCCONbits.LOCK != 1){
    delay(1);
}
digitalWrite(B, 2, HIGH);

    while (1) {
        asm(" btg PORTB, #3 ");
    }
    return 0;
}
