
 .include "p33EV32GM002.inc"



  config __FOSCSEL,  FNOSC_FRC  & IESO_OFF
  config __FOSC,     OSCIOFNC_ON
  config __FWDT, FWDTEN_OFF
  config __FDMT  DMTEN_DISABLE
  config  __FDEVOPT,  PWMLOCK_OFF




.bss
.org 0
zacstack:
 .space 40
konstack:
.space 8

.text

 .global __reset

.org 0
__reset:



	    mov #zacstack, W15
	    mov #konstack, W0
	    mov W0, SPLIM

	    clr ANSELB

	    mov #0xffff, W0
	    mov W0, TRISB
	    bclr TRISB, #15
	    bclr TRISB, #14
	    bclr TRISB, #13
	    bclr TRISB, #12


	    MOV #0x0000, W0
	    MOV W0, PTCON2	;delicka
	    MOV #3684, W0
	    MOV W0, PTPER	;perioda


	    MOV #0, W0
	    MOV W0, PHASE1	;posun
	    MOV #367, W0
	    MOV W0, PDC1	;strida
	    MOV #0, W0
	    MOV W0, DTR1
	    MOV W0, ALTDTR1
	    MOV #0xC400, W0
	    MOV W0, IOCON1
	    MOV #0x0000, W0
	    MOV W0, PWMCON1
	    
	    MOV #0x0003, W0
	    MOV W0, FCLCON1

	    MOV #0x8000, W0	;poveleni pwm
	    MOV W0, PTCON


cyklus:	    nop
	    goto cyklus

.end
