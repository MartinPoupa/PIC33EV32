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


int buffer = 0;
int test = 0;

void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;

    int input = analogRead(B, 0);

    int output = input - buffer + 0x0800;
    if(output < 0){
        output = 0;
    }
    else if (output > 0x0FFF){
        output = 0x0FFF;
    }

    buffer = input;
    DA(B, output);

    if(test){
        DA(A,0x0FFF);
        test = 0;
    }
    else{
        DA(A,0);
        test = 1;
    }
}

int main() {
    pinMode(B, 0, INPUT);
    pinAD(B, 0, ANALOG);
    pinPull(B, 0, DOWN);

    setDA();
    FrequencyT2(35000);
    startInterrupts();
    while (1) {
        delay(1);
    }
    return 0;
}
