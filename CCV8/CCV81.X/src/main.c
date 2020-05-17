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
    //pwm
    pinMode(B, 15, OUTPUT);
    pinMode(B, 14, OUTPUT);

    //control pins
    pinMode(B, 0, INPUT);
    pinMode(B, 1, INPUT);

    //pwm
    pinAD(B, 15, DIGITAL);
    pinAD(B, 14, DIGITAL);

    //control pins
    pinAD(B, 0, DIGITAL);
    pinAD(B, 1, DIGITAL);

    //control pins
    pinPull(B, 0, UP);
    pinPull(B, 1, UP);



    int pwmF = 3684;

    PTCON2 = 0;
    PTPER = pwmF;

    PHASE1 = 0;
    PDC1 = pwmF / 5;
    DTR1 = 0;
    ALTDTR1 = 0;

    IOCON1 = 0xC400;
    PWMCON1 = 0;
    FCLCON1 = 0x0003;

    PTCON = 0x8000;

    while (1) {
        delay(1);
        if(digitalRead(B, 0)){
            if(digitalRead(B, 1)){
                PDC1 = (pwmF / 5) * 4;
            }
            else{
                PDC1 = (pwmF / 5) * 3;
            }
        }
        else{
            if(digitalRead(B, 1)){
                PDC1 = (pwmF / 5) * 2;
            }
            else{
                PDC1 = (pwmF / 5) * 1;
            }
        }
    }
    return 0;
}
