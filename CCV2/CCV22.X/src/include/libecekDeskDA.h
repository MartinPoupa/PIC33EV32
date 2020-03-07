
void setDA (){
    //set pins
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(13, OUTPUT);
    pinAD(5, DIGITAL);
    pinAD(6, DIGITAL);
    pinAD(13, DIGITAL);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(13, HIGH);

    //PPS
    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPINR22 = 0x2600;
    RPOR1 = 0x0800;
    RPOR2 = 0x0090;
    __builtin_write_OSCCONL(OSCCON |  0x40);

    SPI2STAT = 0x0000;
    int cteni = SPI1BUF;

    SPI2CON1 = 0x0520;
    SPI2CON2 = 0 ;

    IFS2bits.SPI2IF = 0;
    IEC2bits.SPI2IE = 1;

    SPI2STATbits.SPIROV = 0;
    SPI2STATbits.SPIEN  = 1;


}


void DA (int convertor, int voltage){
    //if((voltage > 4096 )&& (voltage <= 0 )){
        digitalWrite(13, LOW);
        int cteni = SPI1BUF ;
        SPI1BUF = (voltage + (0x8000 * convertor));
    //}
}

void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)  {
      IFS2bits.SPI2IF = 0;
      digitalWrite(13, HIGH);

}
