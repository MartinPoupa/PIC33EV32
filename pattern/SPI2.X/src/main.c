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


int state = 0;
int voltageDA = 0;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {

    IFS0bits.T2IF = 0;
    if (voltageDA == 0x0fff) {
        digitalWrite(1, LOW );
        state = 1;
    }
    if (voltageDA == 0x0000) {
        digitalWrite(1, HIGH );
        state = 0;
    }

    if (state == 0) {
        DA(A, voltageDA);

        voltageDA++;
    }
    else{
        DA(A, voltageDA);
        voltageDA = voltageDA - 1;
    }



}

int main() {
      pinMode(0, OUTPUT);
      pinAD(0, DIGITAL);
      pinMode(1, OUTPUT);
      pinAD(1, DIGITAL);

      FrequencyT2(1000);
      setDA();

      SPI2STATbits.SPIROV = 0 ;

      SPI2STATbits.SPIEN = 1 ;

      IEC0bits.T2IE = 1;
      IEC2bits.SPI2IE = 1 ;

      INTCON2bits.GIE = 1;

      //startInterrupts();

      DA(A, 0x0fff);


    while (1) {
        delay(1);
    }

    return 0;
}
/*

  */
