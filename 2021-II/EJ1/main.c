/* 
 * File:   main.c
 * Author: josed
 *
 * Created on 8 de febrero de 2022, 01:41 PM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC     = XT    // Oscillator Selection bits (XT oscillator)
#pragma config WDTE     = OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE    = OFF   // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN    = OFF   // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP      = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD      = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT      = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP       = OFF   // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <PIC16F877A.h>

//#include "C:\Program Files\Microchip\xc8\v2.32\pic\include\proc\pic16f877A.h"

#define true        1
#define _XTAL_FREQ  4000000

int main ()
{
    
    // PORTA entrada.
    TRISA = 0x3F;
    ADCON1 = 0x06;
    
    // PORTB salida.
    TRISB = 0x00;    

    while(true)
    {
        
        if(PORTA == 0x01)
        { 
            PORTB = 0x00;
            __delay_ms(500);
            PORTB = 0xFF;
            __delay_ms(500);
        }
        else if(PORTA == 0x02)
        {    
            PORTB = 0x0F;
            __delay_ms(500);
            PORTB = 0xF0;
            __delay_ms(500);
        }
        else
        {
           PORTB = 0x00; 
        }
    }
    
    
}