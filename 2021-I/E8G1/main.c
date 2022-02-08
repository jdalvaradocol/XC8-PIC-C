/* 
 * File:   main.c
 * Author: Jose David
 *
 * Created on 16 de septiembre de 2021, 08:36 AM
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
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCDDIS = OFF     // Zero-cross detect disable (Zero-cross detect circuit is always enabled.)
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

#define     true            1
#define     salida          PORTD

/*
 * 
 */
int main() {

    OSCCONbits.SPLLEN   = 0;    //  4 x PLL deshabilitado
    
    // OPC 1 IRCF
    
    OSCCONbits.IRCF     = 13;   //  4 MHZ
    
    // OPC 2 IRCF       
    
    OSCCONbits.IRCF0 = 1;       // 4 MHz              
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF3 = 1;
    
    // OPC 1 SCS OSC INT

    OSCCONbits.SCS = 3;
    
    // OPC 2 SCS OSC INT

    OSCCONbits.SCS0 = 1;
    OSCCONbits.SCS1 = 1;
    
    // OPC Configuracion registro 8 bits
    // PLL off
    // 4 MHz
    // OSC INT
    
    OSCCON = 0x6B;
    
    OSCSTAT = 0x00; 
    OSCTUNE = 0x00; 
  
    // AN-0 como entrada analoga.
    
    TRISAbits.TRISA0 = 1;   // RA0 ENTRADA
    ANSELAbits.ANSA0 = 1;   // RA0 ANALOGO
    LATAbits.LATA0   = 0;   // LAT RA0 DESACTIVADO
    WPUAbits.WPUA0   = 0;   // WPU RA0 DESACTIVADO
    
    // Configuracion del ADC
    
    ADC_Init( ADPREF_VDD, ADNREF_VSS, ADFM_RIGHT, FOSC16);
  
    // RA2 salida analogo
    
    TRISAbits.TRISA2 = 0;   // RA2 SALIDA
    ANSELAbits.ANSA2 = 1;   // RA2 ANALOGO
    LATAbits.LATA2   = 0;   // LAT RA0 DESACTIVADO
    WPUAbits.WPUA2   = 0;   // WPU RA0 DESACTIVADO
    
    // Configuracion del DAC
    
    DAC1_Init_OUT1(DAC1PSS_VDD, DAC1NSS_VSS);    
       
    // PORTD salida
    
    TRISD   =   0x00;       //  8 bits de salida
    ANSELD  =   0x00;       //  8 bits digitales
    LATD    =   0x00;       //  8 bits Latch borrado
    WPUD    =   0x00;       //  PULL- UP off
    ODCOND  =   0x00;       //  ODCONA off
    SLRCOND =   0x00;       //  slew max
    INLVLD  =   0x00;       //  TTL    
         
    // PORTC salida
    
    ANSELC  =   0x00;       //  8 bits digitales
    LATC    =   0x00;       //  8 bits Latch borrado
    WPUC    =   0x00;       //  PULL- UP off
    
    Lcd_Init();  
 
    int adc;
    char buffer[20];
        
    while(true)   
    {
        
        DAC1_escribir_OUT1(255);
        
        adc = ADC_leer(AN0);
        
        sprintf(buffer,"ADC = %4d ",adc);
        Lcd_Out2(1,0,buffer);
        __delay_ms(100);
         
    }
    
    return (EXIT_SUCCESS);
}

