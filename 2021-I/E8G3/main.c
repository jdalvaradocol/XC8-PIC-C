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
#include "adc.h"
#include "dac.h"

#define     _XTAL_FREQ      1000000
#define     true            1
#define     salida          PORTD

/*
 * 
 */
int main() 
{
    // Opcion 1   
    OSCCONbits.SPLLEN   =  0;     // 4 x PLL off.
    OSCCONbits.IRCF     = 11;     // 1 MHz
    OSCCONbits.SCS      =  2;     // INTFOSC

    OSCSTAT = 0x00;
    OSCTUNE = 0x00;
    
    // ADC init
        
    ADC_Init(ADPREF_VDD, ADNREF_VSS, ADFM_DER, FOSC2);
    
    // AN-0 - RA0 Entrada y analogo.
    
    TRISAbits.TRISA0    = 1;
    ANSELAbits.ANSA0    = 1;
    LATAbits.LATA0      = 0;
    WPUAbits.WPUA0      = 0;
    
    // DAC init
    
    DAC1_Init_E1(P_VDD, N_VSS);

    // RA2 salida y analogo.
    
    TRISAbits.TRISA2    = 0;
    ANSELAbits.ANSA2    = 1;
    LATAbits.LATA2      = 0;
    WPUAbits.WPUA2      = 0;
    
    // PORTD salida.
    
    TRISD   = 0x00;
    ANSELD  = 0x00;
    WPUD    = 0x00;
    LATD    = 0x00;
       
    // PORTC LCD.
    
    ANSELC  = 0x00;
    WPUC    = 0x00;
    LATC    = 0x00;
       
    Lcd_Init();
    
    char buffer[20];
    
    int adc = 0;
    
    while(true)
    {
        
        DAC1_salida(60);
        
        adc = ADC_Lectura(AN0);
        
        sprintf(buffer,"ADC = %4d ",adc);
        Lcd_Out2(1,0,buffer);
        __delay_ms(200);     
    }  
    return (EXIT_SUCCESS);
}

