


/*
void FrequencyT2(int divisor,int frequency) {
    if(divisor == 1){
        T2CON = 0x8000; // 1
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(divisor == 8){
        T2CON = 0x8010; // 8
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(divisor == 64){
        T2CON = 0x8020; // 64
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(divisor == 256){
        T2CON = 0x8030; // 256
        PR2 = ((CYCLE_FREQUENCY * 1000000) / divisor) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }

}


*/
