//#include "p33EV32GM002.h"
//#include "mainFuncion.h"

void FrequencyT2(unsigned int frequency) {
    if(frequency > 64){
        T2CON = 0x8000; // 1
        PR2 = CYCLE_FREQUENCY / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(frequency <= 64 && frequency > 8){
        T2CON = 0x8010; // 8
        PR2 = (CYCLE_FREQUENCY / 8) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(frequency <= 8){
        T2CON = 0x8020; // 64
        PR2 = (CYCLE_FREQUENCY / 64) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
}
