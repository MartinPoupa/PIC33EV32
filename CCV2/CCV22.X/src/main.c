/*
* File:   main.c
* Author: Martin Poupa
*
*/

#include "p33EV32GM002.h"

#include"include/mainFuncion.h"
#include"include/libecekDeskDA.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

/*
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)  {
      IFS0bits.T2IF = 0;
      //sendToSPI(0xffff);
}

*/
/*
 *
 */
int main() {

    setDA();
    startInterrupts();

    while (1) {
        DA(A, 0x0000);
        delay(200);
        DA(A, 0x0fff);
        delay(200);
    }

    return 0;
}
