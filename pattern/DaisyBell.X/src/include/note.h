#define C1 261
#define D1 293
#define E1 329
#define F1 349
#define G1 392
#define A1 440
#define B1 493

#define C2 523
#define D2 587
#define E2 659
#define F2 698
#define G2 784
#define A2 880
#define B2 988

#define C3 1047
#define D3 1175
#define E3 1319
#define F3 1397
#define G3 1568
#define A3 1760
#define B3 1976
#define C4 2093


int state = 0;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if(state){
        DA(A, 0x0fff);
        state = 0;
    }
    else{
        DA(A, 0);
        state = 1;
    }
}


void note (int frequency, int time){
    FrequencyT2(frequency);
    delay(time);
}
