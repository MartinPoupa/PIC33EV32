/*
* File:   main.c
* Author: Martin Poupa
*
* Created on 2. prosince 2018, 16:43
*/

#include "p33EV32GM002.h"
#include <math.h>

#include"include/mainFuncion.h"


#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut

int sinusFrequency = 1000;
int sinusSampleFrequency = 10000;



float yz2 = 0;
float yz1 = 0;
int start = 0;

float sinus(float frequency, float sampleFrequency){
	float theta =  2*PI*(frequency / sampleFrequency);
	float x = 0;
	if(start == 0){
		x = sin(theta);
        start = 1;
	}
	float y = 2 * yz1 * cos(theta) - yz2 + x;
	yz2 = yz1;
	yz1 = y;
	return y;
}

void sendToSPI(unsigned int value){
    unsigned int cteni = SPI1BUF;
    SPI1BUF = value;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)  {
      IFS0bits.T2IF = 0;
      int amplitude = sinus(sinusFrequency, sinusSampleFrequency) * 0x7FFF;
      sendToSPI(amplitude);
}

void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)  {
      IFS0bits.SPI1IF = 0;
}



int f = 0;

void toneT2B2(int frequency) {
    PR2 = ((CYCLE_FREQUENCY * 1000000) / 256) / frequency ;
    T2CON = 0xA030; // 256
    IEC0bits.T2IE = 1;
}

/*
 *
 */
int main() {


    TRISA = 0x0;

    TRISB = 0x00;
    PORTB = 0;
    PORTA = 0;

    ANSELB = 0;
    ANSELA = 0;

    toneT2B2(10000);

    SPI1STAT = 0x0000;
    SPI1CON1 = 0x0520;
    SPI1CON2 = 0 ;

    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIEN  = 1;

    /*  povoluji preruseni  od citace  */
    IEC0bits.SPI1IE = 1;

    /*  globalni povoleni preruseni, tohle se musi povolit,
     * jinak nebude zadne preruseni krome TRAP   */
    INTCON2bits.GIE = 1;

    while (1) {
        PORTBbits.RB0 = 1;
        delay(1000);
        PORTBbits.RB0 = 0;
        delay(1000);
    }

    return 0;
}
