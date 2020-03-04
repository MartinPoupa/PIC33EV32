
            .include "p33EV32GM002.inc"


		    ;.bss
		    ;.text

		    .global _delay
_delay:		      W0, stop
			     repeat #7368
			              nop
stop:		     nop
		         return






;            .global _pinMode
;_pinMode:     do W0, stop
;                repeat #7365
;                    nop
;stop:           nop
;            return




            .end
