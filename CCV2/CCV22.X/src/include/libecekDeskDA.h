
void setDA (){
    //set pins
    pinMode(5, INOUT);
    pinMode(6, INPUT);
    pinMode(13, OUTPUT);
    pinAD(5, DIGITAL);
    pinAD(6, DIGITAL);
    pinAD(13, DIGITAL);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(13, HIGH);

    //PPS



    int cteni = SPI1BUF;

    SPI1CON1 = 0x0520;

    SPI1CON2 = 0 ;

    SPI1STAT = 0x0000;

    IFS0bits.SPI1IF = 0;


    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIEN  = 1;

    IEC0bits.SPI1IE = 1;
    INTCON2bits.GIE = 1;


}


void DA (int convertor, int voltage){
    //if((voltage > 4096 )&& (voltage <= 0 )){
        digitalWrite(13, LOW);
        int cteni = SPI1BUF ;
        SPI1BUF = (voltage + (0x8000 * convertor));
        delay(5);
        digitalWrite(13, HIGH);
    //}
}

void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)  {
      IFS0bits.SPI1IF = 0;
      digitalWrite(13, HIGH);

}
