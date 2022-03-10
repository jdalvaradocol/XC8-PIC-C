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
#include <math.h>

#include "lcd.h"
#include "adc.h"
#include "motorPaP.h"

#define _XTAL_FREQ  16000000  
#define SALIDA      PORTD   

int bandera = 0;

void __interrupt()  isr(void)
{
    if(INTCONbits.IOCIF == 1)
    {   
        if(IOCBFbits.IOCBF4 == 1)
        {
            bandera = 1;
            IOCBFbits.IOCBF4 = 0;
        }
        else if(IOCBFbits.IOCBF5 == 1)
        {
            bandera = 2;
            IOCBFbits.IOCBF5 = 0;
        }
        else if(IOCBFbits.IOCBF6 == 1)
        {
            bandera = 3;
            IOCBFbits.IOCBF6 = 0;
        }
        else if(IOCBFbits.IOCBF7 == 1)
        {
            bandera = 4;
            IOCBFbits.IOCBF7 = 0;
        }
        
        INTCONbits.IOCIF = 0;
    }
    
    if(INTCONbits.TMR0IF == 1)
    {
        PORTDbits.RD7 ^= 0x01;
        TMR0 = 99;      // Carga del TMR0
        INTCONbits.TMR0IF = 0;
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

    // Puerto RA0 como entrada analoga.
    
    TRISA   = 0x01;
    LATA    = 0x00;
    WPUA    = 0x00;
    ANSELA  = 0x01;
    
    // Puerto C como entrada.
    
    TRISC   = 0xC0;
    LATC    = 0x00;
    WPUC    = 0xC0;
    ANSELC  = 0x00;

    // Puerto D como salida.
    
    TRISD   = 0x00;
    LATD    = 0x00;
    WPUD    = 0x00;
    ANSELD  = 0x00;
    
    // IOC PORTC flanco negativo.
    
    IOCCNbits.IOCCN6 = 1;   // Activa la interrupcion RC6
    IOCCNbits.IOCCN7 = 1;   // Activa la interrupcion RC7
        
    // IOC PORTB por flanco positivo
    IOCBPbits.IOCBP4 = 1; //Activa la interrupción de RB0
    IOCBPbits.IOCBP5 = 1; //Activa la interrupción de RB1
    IOCBPbits.IOCBP6 = 1; //Activa la interrupción de RB2
    IOCBPbits.IOCBP7 = 1; //Activa la interrupción de RB3
    
    // Activar pull-up globlal.
    
    OPTION_REGbits.nWPUEN = 0;
    
    // Configurar TMR0.
    
    OPTION_REGbits.TMR0CS   = 0;  // Fosc/4
    OPTION_REGbits.PSA      = 0;  // Activa el pre-escalar1:1
    OPTION_REGbits.PS       = 7;  // 1:256   
    // Activan las interrupciones 
    
    // Configuracion del ADC

    // ADCON1bits.ADPREF = 0;  // Vref+ =  VDD
    // ADCON1bits.ADNREF = 0;  // Vref- =  Vss    
    // ADCON1bits.ADFM = 1;    // Justificado a la derecha
    // ADCON1bits.ADCS = 6;    // Fosc/64 

    ADC_Init(VDD, VSS, RJ, FOSC64);

    Lcd_Init();
    
    INTCONbits.TMR0IE = 1;  // Activa las interrupciones de TMR0.
    INTCONbits.IOCIE = 1;   // Activa las interrupciones de IOC.
    INTCONbits.GIE   = 1;   // Activa las interrupciones Globales. 
        
    char buffer[20]; 
    
    TMR0 = 0;
    
    int adc = 0;
    
    //PORTD = 255;
    
    while(1)
    {
        
        adc = ADC_leer(CH0);
        
        motorPaP(DERECHA, 2000, &SALIDA);

        sprintf(buffer,"adc = %2d",adc);
        Lcd_Out2(2,0,buffer);
       
    }
    
}
