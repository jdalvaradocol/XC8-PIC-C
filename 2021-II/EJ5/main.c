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
#include <stdio.h>
#include <stdlib.h>


#define _XTAL_FREQ  16000000  
#define Salida      PORTD   

#include "lcd.h"

int bandera = 0;

void __interrupt()  isr(void)
{
    if(INTCONbits.IOCIF == 1)
    {
        if(IOCCFbits.IOCCF6 == 1)
        {
            
            bandera = 1;
            
            IOCCFbits.IOCCF6 = 0;
        }
        else if(IOCCFbits.IOCCF7 == 1)
        {
            
            bandera = 2;
            
            IOCCFbits.IOCCF7 = 0;
        }        
      
        INTCONbits.IOCIF = 0;
    }

}

void main() 
{
    // OPC 1
    // OSC = INT, PLL = OFF, FREC = 16 MHz
    OSCCON = 0x7B;
    
    // OPC 2
    OSCCONbits.SPLLEN   = 0;        // PLL = OFF
    OSCCONbits.IRCF     = 0x0F;     // FREC = 16 MHz
    OSCCONbits.SCS      = 0x03;     // OSC = INT
    
    // Puerto C como entrada.
    
    TRISC   = 0xC0;
    LATC    = 0x00;
    WPUC    = 0xC0;
    ANSELC  = 0x00;
    
    // IOC PORTC flanco negativo.
    
    IOCCNbits.IOCCN6 = 1;   // Activa la interrupcion RC6
    IOCCNbits.IOCCN7 = 1;   // Activa la interrupcion RC7
    
    // Puerto B como salida.
    
    TRISD   = 0x00;
    LATD    = 0x00;
    WPUD    = 0x00;
    ANSELD  = 0x00;
    
    // Activar pull-up globlal.
    
    OPTION_REGbits.nWPUEN = 0;
    
    // Activan las interrupciones 
    
    Lcd_Init();
    
    INTCONbits.IOCIE = 1; // Activa las interrupciones de IOC.
    INTCONbits.GIE   = 1; // Activa las interrupciones Globales. 
    
    Lcd_Out(0,0,"Universidad UPTC");
    
    char buffer[20]; 
    
    while(1)
    {
        
        sprintf(buffer,"Bandera = %d",bandera);
        
        Lcd_Out2(3,0,buffer);

        if(bandera == 1)
        {
            Salida = 0xF0;
           __delay_ms(400);
           Salida = 0xC0;
           __delay_ms(400);
        }
        else if(bandera == 2)
        {
            Salida = 0x30;
           __delay_ms(400);
           Salida = 0xC0;
           __delay_ms(400);
        }       
        else
        {
            Salida = 0;
        }
       
    }
    
}
