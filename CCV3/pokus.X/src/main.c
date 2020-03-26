#include "p33EV32GM002.h"

//Nastaveni oscilatoru (FRC, OSC2 jako pin, jedno prenastaveni PPS, WD vypnut)
#pragma config FNOSC = FRC
#pragma config OSCIOFNC = ON
#pragma config IOL1WAY = ON
#pragma config FWDTEN = OFF

int i = 0;

//Tady sou vzorky karla, celkem 100
int hodnekarlu[] = {2048, 2177, 2305, 2432, 2557, 2681, 2802, 2920, 3035, 3145, 3252, 3353, 3450, 3541, 3626, 3705, 3777, 3843, 3901, 3952, 3996, 4032, 4060, 4080, 4092, 4096, 4092, 4080, 4060, 4032, 3996, 3952, 3901, 3843, 3777, 3705, 3626, 3541, 3450, 3353, 3252, 3145, 3035, 2920, 2802, 2681, 2557, 2432, 2305, 2177, 2048, 1919, 1791, 1664, 1539, 1415, 1294, 1176, 1061, 951, 844, 743, 646, 555, 470, 391, 319, 253, 195, 144, 100, 64, 36, 16, 4, 0, 4, 16, 36, 64, 100, 144, 195, 253, 319, 391, 470, 555, 646, 743, 844, 951, 1061, 1176, 1294, 1415, 1539, 1664, 1791, 1919, 2048};


void  main() {

    //V?ecko je vystup
    TRISB = 0;
    ANSELB = 0;
    TRISA = 0;
    ANSELA = 0;

    //Vypnou se portiky
    PORTA = 0;
    PORTB = 0;

    //nastavi se picitadlo na 10kHz
    PR2 = 368;
    T2CON = 0x8000;

    //Nastavi se piniky na prevodnik (karel je kopyto)
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPOR1 = 0x0800;
    RPOR2 = 0x0009;
    RPINR22 = 0x2600;
    __builtin_write_OSCCONL(OSCCON |  0x40);

    SPI2STAT = 0x0000;
    //Nastavi se spi
    SPI2CON1 = 0x053C;
    SPI2CON2 = 0x0000;
    //tady se to v?ecko povolí
    IFS2bits.SPI2IF = 0;
    SPI2STATbits.SPIROV = 0;
    SPI2STATbits.SPIEN = 1;
     IEC0bits.T2IE = 0x01;
    IEC2bits.SPI2IE = 1;
    INTCON2bits.GIE = 0x01;

    while(1) {

    }

}

void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void)  {
      IFS2bits.SPI2IF = 0;
      //kdyz se odvysila, prdne se pin zas na 1
      PORTBbits.RB13 = 1;

}

void __attribute__((interrupt, shadow, auto_psv)) _T2Interrupt(void) {
    //Vynuluje interrupt flag
    IFS0bits.T2IF = 0;
    //prej se to musi precist
    int karel = SPI2BUF;
    PORTBbits.RB13 = 0;

    //tady se tam prdne napeti
    SPI2BUF = 0x1000 | hodnekarlu[i];

    //hlida se pole karlu aby nepreteklo
    if(i < 100){
        i = i + 1;
    }else{
        i = 0;
    }

}
