
            .include "p33EV32GM002.inc"


		    ;.bss
		    ;.text

		    .global _delay
_delay:		      do W0, stop
			     repeat #7368
			              nop
stop:		     nop
		         return



            .end



