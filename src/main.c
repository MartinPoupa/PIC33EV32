/*
* File:   skeleton.c
* Author: kubalik
*
* Created on 2. prosince 2018, 16:43
*/



#include "p33EV32GM002.h"





/*  nasledujici makra nastavuji oscilator
* hledame v header file
*      * Macros for setting device configuration registers
*  pin OSC1 jako I/O pin
* vypinaji Watchdog - opet se podivejte do header file, co vsecno se da nastavit
*
* a mame trochu problem.
* Vetsina prikladu je udelana na starsi versi kompilatoru
* kde se pouzivaji k nastaveni fuses makra jako
_FOSCSEL( FNOSC_FRC )
_FOSC( OSCIOFNC_ON &  IOL1WAY_OFF)
_FWDT( FWDTEN_OFF )

ale to nas kompilator nesnasi. Prevod najdete na
* file:///C:/Program%20Files%20(x86)/Microchip/xc16/v1.33/docs/config_docs/33EV32GM002.html
* nebo v obdobnem adresari , podle toho, kam jste si nainstalovali XC16
*
*
* prevod je nasledujici
*
* _FOSCSEL( FNOSC_FRC )
* registr   FNOSC	Initial oscillator Source Selection Bits
FNOSC = FRC	Internal Fast RC (FRC)
*
*
_FOSC( OSCIOFNC_ON &  IOL1WAY_OFF)
*
*
*
_FWDT( FWDTEN_OFF )

*
*
*
*
*
*  */


#pragma config FNOSC = FRC     //  pracujeme s FRC oscilatorem 7.37MHz
#pragma config OSCIOFNC = ON   //OSC2 is general purpose digital I/O pin
#pragma config IOL1WAY = ON    //Allow Only One reconfiguration pro PPS
#pragma config FWDTEN = OFF	   // WDT and SWDTEN Disabled    Watchdog vypnut




void  main() {

    asm(" nop " );
    asm(" nop " );
    asm(" nop " );
    asm(" nop " );
    asm(" nop " );

    while(1) {

        asm(" nop " );
        asm(" nop " );
        asm(" nop " );
        asm(" nop " );
        
    }
}
