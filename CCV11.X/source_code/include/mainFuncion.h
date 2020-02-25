#define  OSCILACION_FREQUENCY 7.37
#define  REPETION_NOP 7.37

void delay(unsigned int milis){
    for (unsigned int i = 0; i < milis; i++) {
        for (unsigned int j = 0; j < 3685; j++) {
            asm(" nop ");
        }
    }
}
