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
#include "lcd.h"

#define     _XTAL_FREQ      500000
#define     true            1
#define     salida          PORTD

int contA = 0, contB = 0;

void __interrupt() isr(void)
{
    if(INTCONbits.IOCIF == 1)
    {
        if(IOCCFbits.IOCCF6 == 1)
        {
            PORTDbits.RD0 ^= 0x01;
            contA++;
            IOCCFbits.IOCCF6 = 0;
        }
          if(IOCCFbits.IOCCF7 == 1)
        {
            PORTDbits.RD1 ^= 0x01;
            contB++;
            IOCCFbits.IOCCF7 = 0;
        }
        
        INTCONbits.IOCIF = 0;
    }



}


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
      
    // PORTD salida.
    
    TRISD   = 0x00;
    ANSELD  = 0x00;
    WPUD    = 0x00;
    LATD    = 0x00;

    // Timer 0 TOCKI - RA4
    
    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 0;
    WPUAbits.WPUA4   = 0;
    LATAbits.LATA4   = 0;
    
    OPTION_REGbits.TMR0SE = 0;  // incrementa de 0 a 1 
    OPTION_REGbits.TMR0CS = 1;  // RA4 como TOCKI
    OPTION_REGbits.PSA = 1;     // Sin prescaler. 
       
    // PORTC LCD.
    
    ANSELC  = 0x00;
    WPUC    = 0x00;
    LATC    = 0x00;
       
    Lcd_Init();
   
    // PORTC interrupciones RC6 y RC7 
    
    // TRISC |= 0xC0;  
    
    // Configurar RC6 y RC7 entrada.
    
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    
    // Habilitar Resistencia de pull-up RC6 y RC7.
    
    WPUCbits.WPUC6 = 1;
    WPUCbits.WPUC7 = 1;
    OPTION_REGbits.nWPUEN = 0;
    
    // Configuracion de las interrupciones RC6 y RC7.
    
    IOCCN = 0xC0;           // Habilita int RC6 y RC7.
    
    INTCONbits.IOCIE = 1;   // Habilita int IOC.
    INTCONbits.GIE = 1;     // Habilita int Goblales.    
    
    char buffer[20];
    int contador=0;
    
    TMR0 = 0;
    
    while(true)
    {
        sprintf(buffer,"Contador = %4d ",contador);
        Lcd_Out2(1,0,buffer);
        contador ++;
        
        sprintf(buffer,"ContA = %4d ",contA);
        Lcd_Out2(2,0,buffer);
     
        sprintf(buffer,"ContB = %4d ",contB);
        Lcd_Out2(3,0,buffer);

        sprintf(buffer,"TMR0 = %4d ",TMR0);
        Lcd_Out2(4,0,buffer);
        
        __delay_ms(1000);     
    }  
    return (EXIT_SUCCESS);
}

