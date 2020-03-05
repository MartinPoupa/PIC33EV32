.include "p33EV32GM002.inc"


 ;.bss
 ;.text

      .global _delay
_delay:		        do W0, stop
             repeat #7365
                 nop
stop:		        nop
      return

      .global _pinMode  ; (int pin , int set)
_pinMode:	        mov #0x0001, W3
         mov #0x000F, W2
         ;ADD W2, W0, W0
         SUBR  W0, W2, W0
         repeat W0
             RRNC W3, W3
             ;RLNC W3, W3
         mov TRISB, W0

         BTSC W1, #0
         goto nullPinMode

             mov #0xFFFF, W2
             XOR W2, W3, W3
             AND W3, W0, W0
             goto endPinMode

nullPinMode:	        IOR W3, W0, W0

endPinMode:	        mov W0, TRISB
      return

      .global _digitalWrite  ; (int pin , int set)
_digitalWrite:	    mov #0x0001, W3
         mov #0x000F, W2
         ;ADD W2, W0, W0
         SUBR  W0, W2, W0
         repeat W0
             ;RLNC W3, W3
             RRNC W3, W3
         mov PORTB, W0

         BTSC W1, #0
         goto nullDigitalWrite
             mov #0xFFFF, W2
             XOR W2, W3, W3
             AND W3, W0, W0
             goto endDigitalWrite

nullDigitalWrite:	    IOR W3, W0, W0

endDigitalWrite:    mov W0, PORTB
      return

       .end
