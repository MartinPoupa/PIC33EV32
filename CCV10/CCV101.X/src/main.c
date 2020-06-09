/*
* File:   main.c
* Author: Martin Poupa
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

//#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
//#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
//#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
//#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config IESO  = OFF     //  Start up device with user selected oscillator source , u nas FRC
#pragma config  FCKSM  =   CSECMD  //  Clock Switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config POSCMD = NONE	//Primary Oscillator disabled
#pragma config OSCIOFNC = OFF   //OSC2 OSC2 is clock output   RA3   pin 10
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


int buffer = 0;
int test = 0;

void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;

    int input = analogRead(B, 0);
    DA(A,input);
    int output = input - buffer + 0x0800;
    if(output < 0){
        output = 0;
    }
    else if (output > 0x0FFF){
        output = 0x0FFF;
    }
    buffer = input;
    DA(B, output);
/*
    if(test){
        DA(A,0x0FFF);
        test = 0;
    }
    else{
        DA(A,0);
        test = 1;
    }*/
}

int main() {
    pinMode(B, 0, INPUT);
    pinAD(B, 0, ANALOG);
    pinPull(B, 0, DOWN);

    pinMode(B, 4, OUTPUT);
    pinAD(B, 4, DIGITAL);

    setDA();
    FrequencyT2(20000);

    __builtin_write_OSCCONL(OSCCON & 0xBF) ;
    RPOR1 = 0x0031;
    __builtin_write_OSCCONL(OSCCON |  0x40) ;



    REFOCON = 0x8000;

    CLKDIV = 0;
    //CLKDIVbits.FRCDIV =  0;
    PLLFBD=31;
    CLKDIVbits.PLLPOST=1;
    CLKDIVbits.PLLPRE=0;

    INTCON2bits.GIE = 0;
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);

    INTCON2bits.GIE = 1;
    //startInterrupts();


    while (OSCCONbits.LOCK != 1){
        delay(1);
    }

    while (1) {
        delay(1);
    }
    return 0;
}
