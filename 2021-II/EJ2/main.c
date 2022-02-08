/* 
 * File:   main.c
 * Author: josed
 *
 * Created on 8 de febrero de 2022, 01:41 PM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC     = XT    // Oscillator Selection bits (XT oscillator)
#pragma config WDTE     = OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE    = OFF   // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN    = OFF   // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP      = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD      = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT      = OFF   // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP       = OFF   // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic.h>
#include <PIC16F877A.h>

//#include "C:\Program Files\Microchip\xc8\v2.32\pic\include\proc\pic16f877A.h"

#define true        1
#define _XTAL_FREQ  4000000
#define DISPLAY     PORTD
#define SEL_DISPLAY PORTC 
#define ENTRADA     PORTA 
#define SALIDA      PORTB 

// Prototipo de las funciones.
unsigned char display(int entrada);

int main ()
{
    
    int contador = 0;

    // Configura el pueto A y E como digitales.
    ADCON1 = 0x06;
    
    // PORTA entrada.
    TRISA = 0x3F;
    
    // PORTB salida.
    TRISB = 0x00;    

    // PORTC salida.
    TRISC = 0x00;  
    
    // PORTD salida.
    TRISD = 0x00;  
    
    while(true)
    {        
       DISPLAY = display(contador);
       SEL_DISPLAY = 0x01;
       
       // contador = contador + 1;
       contador += 1;
       
       if(contador == 6)
       {
           contador = 0;
       }
       
       SALIDA ^= 0xFF;
       __delay_ms(500);
        
    }
}

unsigned char display(int entrada)
{
    unsigned char display;
    
    if(entrada == 0x00)
    {
       display = 0xBF; 
    }
    else if(entrada == 0x01)
    {
       display = 0x86; 
    }
    else if(entrada == 0x02)
    {
       display = 0xDB; 
    }
    else if(entrada == 0x03)
    {
       display = 0xCF; 
    }
    else if(entrada == 0x04)
    {
       display = 0xE6; 
    }
    else if(entrada == 0x05)
    {
       display = 0xED; 
    }
    else if(entrada == 0x06)
    {
       display = 0xFD; 
    }
    else if(entrada == 0x07)
    {
       display = 0x87; 
    }
    else if(entrada == 0x08)
    {
       display = 0xFF; 
    }
    else if(entrada == 0x09)
    {
       display = 0xEF; 
    }
    else
    {
        display = 0x00;
    }
    
    return display;
}