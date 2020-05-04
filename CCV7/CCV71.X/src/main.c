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

int tik = 0;
int overclock = 1;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    asm(" btg PORTB, #0 ");

    if(tik <= 5){
        tik++;
    }
}


int main() {

    pinMode(B, 0, OUTPUT);
    pinAD(B, 0, DIGITAL);

    FrequencyT2(2);
    startInterrupts();



    while (1) {

        if(tik >= 5 && overclock == 1){
            __builtin_write_OSCCONL(OSCCON & 0xBF) ;
            RPOR1 = 0x0031;
            __builtin_write_OSCCONL(OSCCON |  0x40) ;


            REFOCON = 0x8000;

            CLKDIV = 0;
            //CLKDIVbits.FRCDIV = 0;
            PLLFBD=73;
            CLKDIVbits.PLLPOST = 0;
            CLKDIVbits.PLLPRE = 0;

            INTCON2bits.GIE = 0;
            __builtin_write_OSCCONH(0x01);
            __builtin_write_OSCCONL(OSCCON | 0x01);

            INTCON2bits.GIE = 1;


            while (OSCCONbits.LOCK != 1){
                delay(1);
            }
            overclock = 0;
        }

    }
    return 0;
}
