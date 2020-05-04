
#include "p33EV32GM002.h"

#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config IESO  = OFF     //  Start up device with user selected oscillator source , u nas FRC
#pragma config  FCKSM  =   CSECMD  //  Clock Switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config POSCMD = NONE	//Primary Oscillator disabled
#pragma config OSCIOFNC = OFF   //OSC2 OSC2 is clock output   RA3   pin 10
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

int cekame = 0;
int stelinka = 1;
int pastelka = 5;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    asm(" btg PORTB, #0 ");
    cekame++;
}


int main() {
    ANSELB = 0;
    TRISB = 0;

    PR2 = 14395;    //cca 1Hz
    T2CON = 0x8000; // 256

    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;

    INTCON2bits.GIE = 1; //povoleni preruseni




    while (1) {

        if(stelinka == 1 && cekame > pastelka * 2){

            __builtin_write_OSCCONL(OSCCON & 0xBF) ;
            RPOR1 = 0x0031;
            __builtin_write_OSCCONL(OSCCON |  0x40) ;


            REFOCON = 0x8000;

            CLKDIV = 0;
            PLLFBD = 168;
            CLKDIVbits.PLLPOST = 0;
            CLKDIVbits.PLLPRE = 5;

            INTCON2bits.GIE = 0;
            __builtin_write_OSCCONH(0x01);
            __builtin_write_OSCCONL(OSCCON | 0x01);

            while (OSCCONbits.LOCK != 1){
            asm(" nop ");
            }
            stelinka = 0;
            INTCON2bits.GIE = 1;
        }

    }
    return 0;
}
