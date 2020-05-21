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

    pinMode(B, 4, OUTPUT);
    pinAD(B, 4, DIGITAL);



    __builtin_write_OSCCONL(OSCCON & 0xBF) ;
    RPOR1 = 0x0031;
    __builtin_write_OSCCONL(OSCCON |  0x40) ;



    REFOCON = 0x8000;

    CLKDIV = 0;
   //CLKDIVbits.FRCDIV =  0;
   PLLFBD=73;
   //CLKDIVbits.PLLPOST=0;
   //CLKDIVbits.PLLPRE=0;

  INTCON2bits.GIE = 0;
   __builtin_write_OSCCONH(0x01);
   __builtin_write_OSCCONL(OSCCON | 0x01);

   INTCON2bits.GIE = 1;


while (OSCCONbits.LOCK != 1){
    delay(1);
}

    while (1) {
        asm(" btg PORTB, #0 ");
    }
    return 0;
}
