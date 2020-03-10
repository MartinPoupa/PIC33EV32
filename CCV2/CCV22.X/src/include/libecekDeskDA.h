
void setDA ()
    //pin set
    pinMode(5, OUTPUT); //  14 sdo
    pinMode(6, OUTPUT); //  15 sck
    pinMode(13, OUTPUT); // 24 cs
    pinAD(5, DIGITAL);
    pinAD(6, DIGITAL);
    pinAD(13, DIGITAL);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(13, HIGH);

    //PPS
    __builtin_write_OSCCONL(OSCCON & 0xBF);

    RPOR1 = 0x0800; //  14 sdo
    RPOR2 = 0x0090; //  15 sck in

    RPINR22 = 0x2600; // 15 sck out

    __builtin_write_OSCCONL(OSCCON |  0x40);

    //SPI
    int cteni = SPI2BUF;
    cteni = SPI2BUF;
    cteni = SPI2BUF;
    cteni = SPI2BUF;

    SPI2STAT = 0;
    SPI2CON1 = 0x053b;
    SPI2CON2 = 0 ;
    SPI2STATbits.SPIEN = 1;
    SPI2STATbits.SPIROV = 0;

    //SPI interapt
    IFS2bits.SPI2IF = 0;
    IEC2bits.SPI2IE = 1;
}


void DA (int convertor, int voltage){
    if(voltage < 0x1000 && voltage >= 0){
        PORTBbits.RB13 = 0;
        int cteni = SPI2BUF ;
        SPI2BUF = (voltage + (0x8000 * convertor) + 0x1000);
    }
}

void __attribute__((interrupt, auto_psv)) _SPI2Interrupt(void)  {
      IFS2bits.SPI2IF = 0;
      PORTBbits.RB13 = 1;
}
