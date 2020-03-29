#define  OSCILACION_FREQUENCY 7370000
#define  CYCLE_FREQUENCY (OSCILACION_FREQUENCY / 2)

#define OUTPUT 0
#define INPUT 1

#define DIGITAL 0
#define ANALOG 1

#define A 0x8000
#define B 0

#define LOW 0
#define HIGH 1

#define DOWN 0
#define UP 1
#define FREE 2




void delay(int t);                              // it waits t seconds

void pinMode(int chanel, int pinNumber, int set);            // set OUTPUT/INPUT
void pinAD(int chanel, int pinNumber, int set);             // set DIGITAL/ANALOG

void digitalWrite(int chanel, int pinNumber, int set);      // set LOW/HIGH
int digitalRead(int chanel, int pinNumber);

void setDA();                                   // sets the DA converter
void DA (int chanel, int value);               // sends value to DA converter

void startInterrupts();                         // enable interrupt
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
