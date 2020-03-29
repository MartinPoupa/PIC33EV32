/*
* File:   main.c
* Author: Matej Kraus and Martin Poupa
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


int voltageDA = 0;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if (voltageDA >= 0x0fff) {
        voltageDA = 0;
    }
    voltageDA++;
    DA(A, voltageDA);

}

int input = 0;
int main() {
    pinMode(B, 0, INPUT);
    pinAD(B, 0, DIGITAL);
    pinPull(B, 0, UP);
    FrequencyT2(820);
    setDA();
    DA(A, 0);
    startInterrupts();



    while (1) {
        /*
        if(digitalRead(B, 0) != input){
            if(digitalRead(B, 0)){
                startInterrupts();
                input = 1;
            }
            else{
                stopInterrupts();
                input = 0;
            }
        }*/
    }
    return 0;
}
