#include "p33EV32GM002.h"
#include "include/mainFuncion.h"
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




    //PORTB jako vystupni, RB2 jako vstupni
    TRISB = 0x0004;
    ANSELB = 0x0000;
    pinMode(B, 0, INPUT);
    pinAD(B, 0, ANALOG);

    pinMode(B, 1, INPUT);
    pinAD(B, 1, ANALOG);


    FrequencyT2(1000);

    //Inicializace
    init();

    //AD1CON1 = 0x8404;
    //AD1CHS0 = 0x0020;

    //Povoleni preruseni

    INTCON2bits.GIE = 0x0001;

    while(1) {

    }

}

void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    //Vynuluje interrupt flag
    IFS0bits.T2IF = 0;

        int voltageA = analogRead(B, 0);
        int voltageA1 = analogRead(B, 1);
        float voltage = adcGetVoltage(voltageA);
        delay(10);
        float voltage1 = adcGetVoltage(voltageA1);
        U2TXREG = (int)voltage + 48;
        U2TXREG = '.';
        U2TXREG = (int)(voltage*10)-(((int)voltage)*10) + 48;
        U2TXREG = (int)(voltage*100)-((int)(voltage*10)*10) + 48;
        IEC1bits.U2TXIE = 0x01;
        delay(10);

        U2TXREG = ' ';
        U2TXREG = '-';
        U2TXREG = ' ';
        IEC1bits.U2TXIE = 0x01;

        delay(10);

        U2TXREG = (int)voltage1 + 48;
        U2TXREG = '.';
        U2TXREG = (int)(voltage1*10)-(((int)voltage1)*10) + 48;
        U2TXREG = (int)(voltage1*100)-((int)(voltage1*10)*10) + 48;

        delay(10);
        IEC1bits.U2TXIE = 0x01;
        U2TXREG = ' ';
        U2TXREG = (char)(13);
        U2TXREG = '\n';

        IEC1bits.U2TXIE = 0x01;
}

void __attribute__((interrupt, shadow, auto_psv)) _U2TXInterrupt(void) {
    //Vynuluje interrupt flag
    IFS1bits.U2TXIF = 0;
    IEC1bits.U2TXIE = 0x00;

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
