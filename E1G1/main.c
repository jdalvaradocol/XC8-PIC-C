/* 
 * File:   main.c
 * Author: Jose David
 *
 * Created on 9 de septiembre de 2021, 07:23 AM
 */

#include <stdio.h>
#include <stdlib.h>

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC     = XT      // Oscillator Selection bits (XT oscillator)
#pragma config WDTE     = OFF     // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE    = OFF     // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN    = OFF     // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP      = OFF     // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD      = OFF     // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT      = OFF     // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP       = OFF     // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <PIC16F877A.h>

#define     _XTAL_FREQ      4000000
#define     true            1

#define     salida      PORTB
#define     entrada     PORTA
#define     IN0         PORTAbits.RA0
#define     IN1         PORTAbits.RA1
#define     IN2         PORTAbits.RA2

/*
 * 
 */
int main() 
{
    //Configuracion de los puertos.
    
    // Puerto A entrada.
    TRISA  = 0x3F;
    ADCON1 = 0x07;
    
    // Puerto B salida.
    TRISB = 0x00;

    while(true)
    {
        
        if(PORTAbits.RA0 == 1)
        {
            salida = 0x03;
            __delay_ms(200);     
            salida = 0x0C;
            __delay_ms(200);
            salida = 0x30;
            __delay_ms(200);
            salida = 0xC0;
            __delay_ms(200);
        }
        if(IN2 == 4)
        {
            salida = 0x81;
            __delay_ms(200);     
            salida = 0x42;
            __delay_ms(200);
            salida = 0x24;
            __delay_ms(200);
            salida = 0x18;
            __delay_ms(200);
        }
        else
        {
            salida = 0;
        }
        
    }
        
    return (EXIT_SUCCESS);
}

