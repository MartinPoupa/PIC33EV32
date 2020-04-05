#define C0 130
#define D0 146
#define E0 164
#define F0 174
#define G0 195
#define A0 220
#define BB0 233
#define B0 247

#define C1 261
#define D1 293
#define E1 329
#define F1 349
#define G1 392
#define A1 440
#define BB1 466
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
int voltageDA = 2047;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if(state){

        state = 0;
        if(voltageDA < 0x0fff){
            voltageDA = voltageDA + 32;
        }
        DA(A, voltageDA);
    }
    else{
        DA(A, 0);
        state = 1;
    }
}

/*
int voltageDA = 0;

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;
    if (voltageDA >= 0x0fff) {
        state = 1;
        voltageDA = 0x0fff;
    }
    if (voltageDA <= 0) {
        state = 0;
        voltageDA = 0;
    }
    DA(A, voltageDA);
    if (state == 0) {
        voltageDA = voltageDA + 512;
    }
    else{
        voltageDA = voltageDA - 512;
    }
}

*/
void note (int frequency, int time){
    voltageDA = 2047;
    FrequencyT2(frequency * 2);
    delay(time);
}
