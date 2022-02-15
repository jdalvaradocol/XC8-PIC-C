/*
 * File:   main.c
 * Author: josed
 *
 * Created on 15 de febrero de 2022, 12:26 PM
 */

// PIC16F1719 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC     = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE     = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE    = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE    = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP       = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN    = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO     = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN    = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT      = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY  = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCDDIS   = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR and can be enabled with ZCDSEN bit.)
#pragma config PLLEN    = OFF      // Phase Lock Loop enable (4x PLL is enabled when software sets the SPLLEN bit)
#pragma config STVREN   = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV     = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR    = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP      = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <pic16F1719.h>

#define _XTAL_FREQ  16000000  
#define Entrada     PORTA  
#define Salida      PORTB   

void main() 
{
    // OPC 1
    // OSC = INT, PLL = OFF, FREC = 16 MHz
    OSCCON = 0x7B;
    
    // OPC 2
    OSCCONbits.SPLLEN   = 0;        // PLL = OFF
    OSCCONbits.IRCF     = 0x0F;     // FREC = 16 MHz
    OSCCONbits.SCS      = 0x03;     // OSC = INT
    
    // Puerto A como entrada.
    
    TRISA   = 0xFF;
    LATA    = 0x00;
    WPUA    = 0x00;
    ANSELA  = 0x00;
    
    // Puerto B como salida.
    
    TRISB   = 0x00;
    LATB    = 0x00;
    WPUB    = 0x00;
    ANSELB  = 0x00;
    
    while(1)
    {
        
        if(Entrada == 1)
        {
            Salida ^= 0xFF;
           __delay_ms(400);
        }
        else if(Entrada == 2)
        {
            Salida = 0x0F;
           __delay_ms(400);
           Salida = 0xF0;
           __delay_ms(400);
        }       
        else
        {
            Salida = 0;
        }
       
    }
    
}
