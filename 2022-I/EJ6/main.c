/*
 * File:   main.c
 * Author: josed
 *
 * Created on 8 de julio de 2022, 07:53 AM
 */

// PIC16F1719 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC     = INTOSC   // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE     = OFF      // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE    = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE    = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP       = OFF      // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN    = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF      // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO     = OFF      // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN    = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT      = OFF      // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY  = OFF      // Peripheral Pin Select one-way control (The PPSLOCK bit can be set and cleared repeatedly by software)
#pragma config ZCDDIS   = ON       // Zero-cross detect disable (Zero-cross detect circuit is always enabled.)
#pragma config PLLEN    = OFF      // Phase Lock Loop enable (4x PLL is enabled when software sets the SPLLEN bit)
#pragma config STVREN   = ON       // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV     = LO       // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR    = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP      = OFF      // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16F1719.h>
#include "configuracion.h"
#include "interrupciones.h"
#include "lcd.h"
#include "adc.h"

#define _XTAL_FREQ 16000000

// Rutina de interrupcion

int Tecla = 0;

// Prototipo de la funcion
unsigned char display(char dato);

int main ()
{
    // Configuracion del uC
    
    configuracion();
    
    // Configuracion TMR0 Delay 10 ms
    
    OPTION_REGbits.TMR0CS   = 0; // Fuente Clock interno
    OPTION_REGbits.PSA      = 0;
    OPTION_REGbits.PS       = 7; 
    TMR0                    = 99;

    // Inicializacion
    
    Lcd_Init();
    adc_Init(ADFM_DERECHA, FOSC_2, VREF_N_VSS, VREF_P_VDD);
    
    DAC1CON0bits.DAC1OE1 = 1;
    DAC1CON0bits.DAC1PSS = 0;
    DAC1CON0bits.DAC1NSS = 0;
    DAC1CON0bits.DACEN = 1;
    
    // Configuracion Interrupciones.
    
    init_interrupciones();


    int   adc = 0; 
    char  dac = 0;
    double adc_volt = 0.0; 
    
    char buffer[20];
    
    Lcd_Out(1,0,"**** ADC 2022-I ****");
    
    while(1)
    {
        dac += 10;
        DAC1CON1 = dac;
        
        adc = adc_Leer(CH0);    
        adc_volt = (adc/1023.0) * 5.0;
         
        sprintf(buffer,"ADC = %i ",adc);
        Lcd_Out2(2,0,buffer);
  
        sprintf(buffer,"Vol = %.2f ",adc_volt);
        Lcd_Out2(3,0,buffer);

        sprintf(buffer,"dac = %i ",dac);
        Lcd_Out2(4,0,buffer);
        
        __delay_ms(500);
 
    }
}