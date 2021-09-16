/* 
 * File:   main.c
 * Author: Jose David
 *
 * Created on 16 de septiembre de 2021, 12:17 PM
 */

#include <stdio.h>
#include <stdlib.h>


// PIC16F1719 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCDDIS = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR and can be enabled with ZCDSEN bit.)
#pragma config PLLEN = OFF      // Phase Lock Loop enable (4x PLL is enabled when software sets the SPLLEN bit)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <PIC16F1719.h>
#include "secuencia.h"

#define     _XTAL_FREQ      4000000
#define     true            1
#define     salida          PORTB
#define     entrada         PORTA

/*
 * 
 */
int main() 
{
    // Opcion 1   
    OSCCONbits.SPLLEN   =  0;     // 4 x PLL off.
    OSCCONbits.IRCF     = 10;      // 500 KHz
    OSCCONbits.SCS      =  2;     // INTFOSC
    // Opcion 2
    OSCCONbits.SPLLEN   = 0;      // 4 x PLL off.
    OSCCONbits.IRCF3    = 1;      // 500 KHz
    OSCCONbits.IRCF2    = 0;      // 500 KHz
    OSCCONbits.IRCF1    = 1;      // 500 KHz
    OSCCONbits.IRCF0    = 0;      // 500 KHz          
    OSCCONbits.SCS1     = 1;      // INTFOSC    
    OSCCONbits.SCS1     = 0;      // INTFOSC    
    // Opcion 3
    OSCCON = 0x52;                // 4 x PLL off, 500 KHz, INTFOSC.
    OSCSTAT = 0x00;
    OSCTUNE = 0x00;
    
    // PORTA entrada.
    
    TRISA   = 0xFF;
    ANSELA  = 0x00;
    WPUA    = 0x00;
    LATA    = 0x00;
    ODCONA  = 0x00;
    INLVLA  = 0x00;
    SLRCONA = 0x00;
        
    // PORTB salida.
    
    TRISB   = 0x00;
    ANSELB  = 0x00;
    WPUB    = 0x00;
    LATB    = 0x00;
    ODCONB  = 0x00;
    INLVLB  = 0x00;
    SLRCONB = 0x00;
        
    while(true)
    {
        secuencia_leds(&salida);
    }  
    
    return (EXIT_SUCCESS);

}

