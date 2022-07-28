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
#include <pic16F1719.h>
#include "configuracion.h"
#include "interrupciones.h"

#define _XTAL_FREQ 16000000

// Rutina de interrupcion

int estado = 0;
int delay = 0;

// Prototipo de la funcion
unsigned char display(char dato);

int main ()
{
    // Configuracion del uC
    
    configuracion();
    
    // Configuracion TMR0 Delay 16 ms
    
    OPTION_REGbits.TMR0CS = 0; // Feunte Clock interno
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 7; 
    
    // Configuracion Interrupciones.

    init_interrupciones();

    int     dato = 0;
    char  unidad = 0;
    char  decena = 0;
    char centena = 0;
    char uni_mil = 0;

    int     contador = 1234; 
    
    while(1)
    {

        if (estado == 0)
        {
            contador = contador;
        }
        else if (estado == 1)
        {
            contador++;
        }
         else if (estado == 2)
        {
            contador--;
        }
       
        dato = contador;
        
        unidad = dato % 10;
        dato = dato / 10;
        decena = dato % 10;
        dato = dato / 10;  
        centena = dato % 10;
        dato = dato / 10;  
        uni_mil = dato % 10;
        dato = dato / 10; 
        
        for(int i=0;i < 50; i++)
        {
            PORTD = ~display(unidad);
            PORTC = 0x01;
            __delay_us(800);
             PORTD = ~display(decena);
            PORTC = 0x02;
            __delay_us(800);
             PORTD = ~display(centena);
            PORTC = 0x04;
            __delay_us(800);
             PORTD = ~display(uni_mil);
            PORTC = 0x08;
            __delay_us(800);
            PORTC = 0x00;
        }
    }
        
}

unsigned char display(char dato)
{
    unsigned char salida = 0;
    
    if (dato == 0)
    {
        salida = 0x40;
    }
    else if(dato == 1)
    {
        salida = 0x79;
    }
    else if(dato == 2)
    {
        salida = 0x24;
    }
    else if(dato == 3)
    {
        salida = 0x30;
    }
    else if(dato == 4)
    {
        salida = 0x19;
    }    
    else if(dato == 5)
    {
        salida = 0x12;
    }
    else if(dato == 6)
    {
        salida = 0x02;
    }
    else if(dato == 7)
    {
        salida = 0x78;
    }
    else if(dato == 8)
    {
        salida = 0x00;
    }
    else if(dato == 9)
    {
        salida = 0x10;
    }
    else
    {
        salida = 0xFF;
    }
    
    return salida;
}