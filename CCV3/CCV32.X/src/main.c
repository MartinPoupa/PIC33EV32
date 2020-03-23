/*
* File:   main.c
* Author: Matej Kraus
*
*/

#include "p33EV32GM002.h"
#include "include/mainFuncion.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut


int i;
unsigned int a;

void main() {
      TRISB=0;
      ANSELB=0;

      PR3=4606;
      T3CON=0xA000;

      i=0;
      a=0;

      setDA();
      startInterrupts();

    while (1) {


    }
}

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void){

  IFS0bits.T3IF=0;

  if(a==4095 || a==0)i=!i;

  if(i)a--;
  else a++;
}
