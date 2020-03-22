#define  OSCILACION_FREQUENCY 7.37
#define  CYCLE_FREQUENCY (OSCILACION_FREQUENCY / 2)

#define OUTPUT 0
#define INPUT 1

#define DIGITAL 0
#define ANALOG 1

#define A 1
#define B 0

#define LOW 0
#define HIGH 1



void delay(int t);                              // it waits t seconds

void pinMode(int pinNumber, int set);           // set OUTPUT/INPUT
void pinAD(int pinNumber, int set);             // set DIGITAL/ANALOG

void digitalWrite(int pinNumber, int set);      // set LOW/HIGH

void setDA();                                   // sets the DA converter
void DA (int chanel, int value );               // sends value to DA converter

void startInterrupts();                         // enable interrupt
void FrequencyT2(int frequency) {
    if(frequency > 64){
        T2CON = 0x8000; // 1
        PR2 = (CYCLE_FREQUENCY * 1000000) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(frequency <= 64 && frequency > 8){
        T2CON = 0x8010; // 8
        PR2 = ((CYCLE_FREQUENCY * 1000000) / 8) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
    else if(frequency <= 8){
        T2CON = 0x8020; // 64
        PR2 = ((CYCLE_FREQUENCY * 1000000) / 64) / frequency ;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    }
}
