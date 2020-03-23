.include "p33EV32GM002.inc"


 ;.bss
 ;.text

                    .global _delay              ; void delay(int);
_delay:		            DO W0, stop
                            REPEAT #7365
                                NOP
stop:		                NOP
                    return

                    .global _pinMode            ; void pinMode(int, int);
_pinMode:	            MOV #0x0001, W3
                        MOV #0x000F, W2
                        SUBR  W0, W2, W0
                        REPEAT W0
                            RRNC W3, W3
                        MOV TRISB, W0

                        BTSC W1, #0
                        GOTO nullPinMode

                          MOV #0xFFFF, W2
                          XOR W2, W3, W3
                          AND W3, W0, W0
                          GOTO endPinMode

nullPinMode:	           IOR W3, W0, W0

endPinMode:	            MOV W0, TRISB
                    return

                    .global _digitalWrite       ; void digitalWrite(int, int);
_digitalWrite:	        MOV #0x0001, W3
                        MOV #0x000F, W2
                        SUBR  W0, W2, W0
                        REPEAT W0
                           RRNC W3, W3
                        MOV PORTB, W0

                        BTSC W1, #0
                        GOTO nullDigitalWrite
                           MOV #0xFFFF, W2
                           XOR W2, W3, W3
                           AND W3, W0, W0
                           GOTO endDigitalWrite

nullDigitalWrite:	       IOR W3, W0, W0

endDigitalWrite:        MOV W0, PORTB
                    return

                    .global _pinAD              ; void pinAD(int, int);
 _pinAD:	            MOV #0x0001, W3
                        MOV #0x000F, W2
                        SUBR  W0, W2, W0
                        REPEAT W0
                            RRNC W3, W3
                        MOV ANSELB, W0
                        BTSC W1, #0
                        GOTO nullPinAD
                            MOV #0xFFFF, W2
                            XOR W2, W3, W3
                            AND W3, W0, W0
                            GOTO endPinAD

 nullPinAD:	                IOR W3, W0, W0

 endPinAD:              MOV W0, ANSELB
                    return














                    .global _startInterrupts    ; void startInterrupts();
 _startInterrupts:	     BSET  INTCON2, #GIE
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

                        ;SPI interapt
                        ;BCLR IFS2, #SPI2IF
                        ;BSET IEC2, #SPI2IE

                    return

                    .global _DA                 ; void DA(int);
_DA:		            BSET W0, #15
                        BCLR W0, #13
                        BSET W0, #12

                        MOV SPI2BUF, W0
                        BCLR PORTB, #13
                        MOV W1, SPI2BUF
                        REPEAT #16
                            NOP
                        BSET PORTB, #13
                    return

;                    .global __SPI2Interrupt     ; SPI interapt
;__SPI2Interrupt:       BSET PORTB, #13
;                       BCLR IFS2, #SPI2IF
                     ;  BTG PORTB, #0
;                    retfie



                    .end
