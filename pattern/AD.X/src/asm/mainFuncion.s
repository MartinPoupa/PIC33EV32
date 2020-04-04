.include "p33EV32GM002.inc"


 ;.bss
 ;.text

                    .global _delay              ; void delay(int);
_delay:		            DO W0, stop
                            REPEAT #7365
                                NOP
stop:		                NOP
                    return

                    .global _pinMode            ; void pinMode(int, int, int);
_pinMode:	            MOV #0x000F, W3
                        SUBR  W1, W3, W1
                        MOV #0x0001, W3
                        REPEAT W1
                            RRNC W3, W3
                        BTSC W0, #15
                        GOTO nullChanelPinMode
                            MOV TRISB, W1
                            GOTO endChanelPinMode
nullChanelPinMode:          MOV TRISA, W1
endChanelPinMode:       BTSC W2, #0
                        GOTO nullSetPinMode
                            MOV #0xFFFF, W2
                            XOR W2, W3, W3
                            AND W3, W1, W1
                            GOTO endSetPinMode
nullSetPinMode:	            IOR W3, W1, W1
endSetPinMode:	        BTSC W0, #15
                        GOTO nullPinMode
       			            MOV W1, TRISB
                            GOTO endPinMode
nullPinMode:                MOV W1, TRISA
endPinMode:             NOP
                    return

                    .global _pinAD            ; void pinAD(int, int, int);
_pinAD:	                MOV #0x000F, W3
                        SUBR  W1, W3, W1
                        MOV #0x0001, W3
                        REPEAT W1
                            RRNC W3, W3
                        BTSC W0, #15
                        GOTO nullChanelPinAD
                            MOV ANSELB, W1
                            GOTO endChanelPinAD
nullChanelPinAD:          MOV ANSELA, W1
endChanelPinAD:       BTSC W2, #0
                        GOTO nullSetPinAD
                            MOV #0xFFFF, W2
                            XOR W2, W3, W3
                            AND W3, W1, W1
                            GOTO endSetPinAD
nullSetPinAD:	            IOR W3, W1, W1
endSetPinAD:	        BTSC W0, #15
                        GOTO nullPinAD
                            MOV W1, ANSELB
                            GOTO endPinAD
nullPinAD:                  MOV W1, ANSELA
endPinAD:             NOP
                    return

                    .global _pinPull            ; void pinPull(int, int, int);
_pinPull:               MOV #0x000F, W3
                        SUBR  W1, W3, W1
                        MOV #0x0001, W3
                        REPEAT W1
                            RRNC W3, W3
                        BTSC W0, #15
                        GOTO nullChanelPinPull
                            MOV CNPDB, W4
                            MOV CNPUB, W5
                            GOTO endChanelPinPull
nullChanelPinPull:           MOV CNPDA, W4
                            MOV CNPUA, W5

endChanelPinPull:       BTSC W2, #0
                        GOTO nullSetPinPull
                            IOR W3, W4, W4
                            MOV #0xFFFF, W2
                            XOR W2, W3, W3
                            AND W3, W5, W5
                            GOTO endSetPinPull
nullSetPinPull:	            IOR W3, W5, W5
                            MOV #0xFFFF, W2
                            XOR W2, W3, W3
                            AND W3, W4, W4
endSetPinPull:	        BTSC W0, #15
                        GOTO nullPinPull
                            MOV W4, CNPDB
                            MOV W5, CNPUB
                            GOTO endPinPull
nullPinPull:                 MOV W4, CNPDA
                            MOV W5, CNPUA
endPinPull:             NOP
                    return


                    .global _digitalWrite            ; void digitalWrite(int, int, int);
_digitalWrite:	        MOV #0x000F, W3
                        SUBR  W1, W3, W1
                        MOV #0x0001, W3
                        REPEAT W1
                            RRNC W3, W3
                        BTSC W0, #15
                        GOTO nullChanelDigitalWrite
                            MOV PORTB, W1
                            GOTO endChanelDigitalWrite
nullChanelDigitalWrite:     MOV PORTA, W1
endChanelDigitalWrite:  BTSC W2, #0
                        GOTO nullSetDigitalWrite
                            MOV #0xFFFF, W2
                            XOR W2, W3, W3
                            AND W3, W1, W1
                            GOTO endSetDigitalWrite
nullSetDigitalWrite:	            IOR W3, W1, W1
endSetDigitalWrite:	        BTSC W0, #15
                        GOTO nullDigitalWrite
                            MOV W1, PORTB
                            GOTO endDigitalWrite
nullDigitalWrite:           MOV W1, PORTA
endDigitalWrite:        NOP
                    return

                    .global _digitalRead       ; void digitalRead(int, int);
_digitalRead:	        BTSC W0, #15
                        GOTO nullDigitalRead
                            MOV PORTB, W0
                            GOTO endDigitalRead
nullDigitalRead:            MOV PORTA, W0
endDigitalRead:         MOV #0x000F, W2
                        ADD  W1, W2, W1
                        REPEAT W1
                           RRNC W0, W0
                        MOV #0x0001, W2
                        AND W0, W2, W0
                    return

                    .global _analogRead              ; void analogRead(int);
_analogRead:            BTSC W0, #15
                            GOTO nullAnalogRead
                                MOV #2, W2
                                ADD W2, W1, W1
                                MOV W1, AD1CHS0

                                GOTO endAnalogRead
nullAnalogRead:                 MOV W1, AD1CHS0
endAnalogRead:          BCLR AD1CON1, #SAMP
                        REPEAT #8
                            NOP
                        MOV ADC1BUF0, W0
                    return



                    .global _startInterrupts    ; void startInterrupts();
 _startInterrupts:	     BSET  INTCON2, #GIE
                    return

                    .global _stopInterrupts    ; void startInterrupts();
 _stopInterrupts:	     BCLR  INTCON2, #GIE
                    return

                    .global _setDA              ; void setDA();
                        ;pin set
 _setDA:	            BCLR TRISB, #5        ;  14 sdo
                        BCLR TRISB, #6        ;  15 sck
                        BCLR TRISB, #13       ;     cs

                        BCLR ANSELB, #5
                        BCLR ANSELB, #6
                        BCLR ANSELB, #13

                        BCLR PORTB, #5
                        BCLR PORTB, #6
                        BSET PORTB, #13

                        ;PPS
                        MOV #OSCCONL, W1
                        MOV #0x46, W2
                        MOV #0x57, W3
                        MOV.B W2, [W1]       ; Write 0x46
                        MOV.B W3, [W1]       ; Write 0x57
                        BCLR OSCCON, #6

                            MOV #0x0800,  W0 ; 14 sdo out
                            MOV W0,  RPOR1

                            MOV #0x0009,  W0 ; 15 sck out
                            MOV W0,  RPOR2

                            MOV #0x2600,  W0 ; 15 sck in
                            MOV W0,  RPINR22

                        MOV #OSCCONL, W1
                        MOV #0x46, W2
                        MOV #0x57, w3
                        MOV.B W2, [W1]       ; Write 0x46
                        MOV.B W3, [W1]       ; Write 0x57
                        BSET OSCCON, #6

                        ; SPI2
                        REPEAT #4
                            MOV SPI2BUF, W0

                        MOV #0x0000, W0
                        MOV W0, SPI2STAT
                        MOV #0x053f, W0
                        MOV W0, SPI2CON1
                        MOV #0x0000, W0
                        MOV W0, SPI2CON2

                        BCLR SPI2STAT, #SPIROV
                        BSET SPI2STAT, #SPIEN
                    return

                    .global _DA                 ; void DA(int, int);
_DA:
                        BCLR W1, #15
                        BCLR W1, #13
                        BSET W1, #12
                        IOR W0, W1, W1
                        MOV SPI2BUF, W0
                        BCLR PORTB, #13
                        MOV W1, SPI2BUF
                        REPEAT #16
                            NOP
                        BSET PORTB, #13
                    return



                    .end
