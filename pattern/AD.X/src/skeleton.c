#include "p33EV32GM002.h"

//Nastaveni oscilatoru (FRC, OSC2 jako pin, jedno prenastaveni PPS, WD vypnut)
#pragma config FNOSC = FRC
#pragma config OSCIOFNC = ON
#pragma config IOL1WAY = ON
#pragma config FWDTEN = OFF

void init();
uint16_t ftoval(int freq, uint16_t presc);
float adcGetVoltage(uint16_t value);

void  main() {

    //RA0 je analog in, zbytek dig out
    TRISA = 0x0001;
    ANSELA = 0x0001;


    //PORTB jako vystupni, RB2 jako vstupni
    TRISB = 0x0004;
    ANSELB = 0x0000;

    //Nastaveni T2
    PR2 = ftoval(1, 256);
    //Delicka 1, citac zapnut
    T2CON = 0x8030;

    //Inicializace
    init();

    AD1CON1 = 0x8404;
    AD1CHS0 = 0x0100;

    //Povoleni preruseni
    IEC0bits.T2IE = 0x01;
    IEC0bits.AD1IE = 0x01;
    INTCON2bits.GIE = 0x0001;

    while(1) {

    }

}

void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    //Vynuluje interrupt flag
    IFS0bits.T2IF = 0;

    //Zacne se prevod
    AD1CON1bits.SAMP = 0;

}

void __attribute__((interrupt, shadow, auto_psv)) _U2TXInterrupt(void) {
    //Vynuluje interrupt flag
    IFS1bits.U2TXIF = 0;
    IEC1bits.U2TXIE = 0x00;

}

void __attribute__((interrupt, shadow, auto_psv)) _AD1Interrupt(void) {
    //Vynuluje interrupt flag
    IFS0bits.AD1IF = 0;

    float voltage = adcGetVoltage(ADC1BUF0);
    U2TXREG = (int)voltage + 48;
    U2TXREG = '.';
    U2TXREG = (int)(voltage*10)-(((int)voltage)*10) + 48;
    U2TXREG = (int)(voltage*100)-((int)(voltage*10)*10) + 48;
    U2TXREG = '\n';

    IEC1bits.U2TXIE = 0x01;


}

float adcGetVoltage(uint16_t value){
    return (float)0.001220703125*(float)value;
}


void init(){

    __builtin_write_OSCCONL(OSCCON & 0xBF);

    //Nastaveni pinu UARTU RB2 - RX, RB3 - TX
    RPINR19 = 0x0022;
    RPOR0 = 0x0300;

    __builtin_write_OSCCONL(OSCCON |  0x50);

    //Konfigurace uartu
    U2BRG = 5;
    U2MODE = 0x0010;
    U2STA = 0x8000;
    //Zapne uarts
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;
}

uint16_t ftoval(int freq, uint16_t presc){
    uint16_t val = ((float)3685000 / (float)presc)/(float)freq;
    return val;
}
