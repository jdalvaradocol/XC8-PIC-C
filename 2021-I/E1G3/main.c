/* 
 * File:   main.c
 * Author: Jose David
 *
 * Created on 9 de septiembre de 2021, 12:30 PM
 */

#include <stdio.h>
#include <stdlib.h>

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC     = XT       // Oscillator Selection bits (XT oscillator)
#pragma config WDTE     = OFF      // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE    = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN    = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP      = OFF      // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD      = OFF      // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT      = OFF      // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP       = OFF      // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <PIC16F877A.h>

#define     true            1
#define     _XTAL_FREQ      4000000
#define     salida          PORTB
#define     entrada         PORTA


/*
 * 
 */
int main()
{

    // configuracion de puertos.
    // Puerto A como entrada.
    TRISA = 0x3F;
    ADCON1 = 0x07; 
    // Puerto B como salida.
    TRISB = 0x00;
    
    while(true)
    {
        if(entrada == 1)
        {
            salida = 0x00;
            __delay_ms(300);
            salida = 0xFF;
            __delay_ms(300);
        }
        else if(entrada == 8)
        {
            salida = 0x0F;
            __delay_ms(300);
            salida = 0xF0;
            __delay_ms(300);
        }
        else
        {
            salida = 0x00;
        }
    }
    
    return (EXIT_SUCCESS);
}

