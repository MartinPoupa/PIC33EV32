
#define  OSCILACION_FREQUENCY 7.37
#define  CYCLE_FREQUENCY (OSCILACION_FREQUENCY / 2)

#define OUTPUT 0
#define INPUT 1

#define A 0
#define B 1

#define LOW 0
#define HIGH 1

#define DIGITAL 0
#define ANALOG 1
/*
void FrequencyT2(int counter,int frequency) {
    PR2 = ((CYCLE_FREQUENCY * 1000000) / 256) / frequency ;
    T2CON = 0xA030; // 256
}

*/

void startInterrupts(){
    INTCON2bits.GIE = 1;
}
