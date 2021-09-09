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
#define     DIG0            PORTC
#define     DIG1            PORTD

// Declaracion de prototipo de las funciones.

unsigned char display(int numero);

int main()
{
    // configuracion de puertos.
    // Puerto A como entrada.
    TRISA = 0x3F;
    ADCON1 = 0x07; 
    // Puerto B como salida.
    TRISB = 0x00;
    // Puerto C como salida.
    TRISC = 0x00;
    // Puerto D como salida.
    TRISD = 0x00;
        
    while(true)
    {
        for(int decena = 0 ;decena <= 3; decena++)
        {
            DIG1 = display(decena);
            
            for(int unidad = 0 ;unidad <= 9; unidad++)
            {
                DIG0 = display(unidad);
                __delay_ms(500);
            }
        
        }
        
    }
    
    return (EXIT_SUCCESS);
}

unsigned char display(int numero)
{
    unsigned char salida_display;
    
          if(numero == 0)   salida_display = 0x40;
    else if (numero == 1)   salida_display = 0x79;
    else if (numero == 2)   salida_display = 0x24;
    else if (numero == 3)   salida_display = 0x30;
    else if (numero == 4)   salida_display = 0x19;
    else if (numero == 5)   salida_display = 0x12;
    else if (numero == 6)   salida_display = 0x02;
    else if (numero == 7)   salida_display = 0x78;
    else if (numero == 8)   salida_display = 0x00;
    else if (numero == 9)   salida_display = 0x10;
    else                    salida_display = 0xFF;

    return salida_display;
    
}
