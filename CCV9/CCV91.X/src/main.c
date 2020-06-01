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


int duty = 0;
int cikle = 0;
int pwmF = 5000;

void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;

    if(cikle){
        digitalWrite(B, 0, 1);
        duty--;
        if(duty <= 0){
            cikle = 0;
        }
    }
    else{
        digitalWrite(B, 0, 0);
        duty++;
        if(duty >= pwmF){
            cikle = 1;
        }
    }
    PDC1 = duty;

}

int main() {
    //pwm
    pinMode(B, 15, OUTPUT);
    pinMode(B, 14, OUTPUT);
    pinAD(B, 15, DIGITAL);
    pinAD(B, 14, DIGITAL);

    pinMode(B, 0, OUTPUT);
    pinAD(B, 0, DIGITAL);

    PTCON2 = 0;
    PTPER = pwmF;

    PHASE1 = 0;
    PDC1 = 0;
    DTR1 = 0;
    ALTDTR1 = 0;

    IOCON1 = 0xC400;
    PWMCON1 = 0;
    FCLCON1 = 0x0003;

    PTCON = 0x8000;

    FrequencyT2(1000);
    startInterrupts();

    while (1) {
        delay(1);
    }
    return 0;
}