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
        digitalWrite(B, 1, 1);
        test = 0;
    }
    else{
        digitalWrite(B, 1, 0);
        test = 1;
    }

}

int main() {
    pinMode(B, 1, OUTPUT);
    pinAD(B, 1, DIGITAL);

    pinMode(B, 0, INPUT);
    pinAD(B, 0, ANALOG);
    setDA();


    FrequencyT2(1000);
    startInterrupts();

    while (1) {
        delay(1);
    }
    return 0;
}