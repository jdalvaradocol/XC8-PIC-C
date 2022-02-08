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

// prototipo de la funcion 

unsigned char  display(int dato);

int main() 
{
   
    //Configuracion de los puertos.
    
    // Puerto A entrada.
    TRISA  = 0x3F;
    ADCON1 = 0x07;
    // Puerto B salida.
    TRISB = 0x00;
    // Puerto C salida.
    TRISC = 0x00;
    // Puerto D salida.
    TRISD = 0x00;
    
    while(true)
    {
        for(int decena = 0; decena < 6; decena++)
        {
            PORTD = display(decena);   
            
            for(int unidad = 0; unidad < 10; unidad++)
            {
                PORTC = display(unidad);
                __delay_ms(500);
            }
      
        }
    }
        
    return (EXIT_SUCCESS);
}

unsigned char display(int dato)
{
    unsigned char salida = 0;
    
         if(dato == 0)  salida = 0x40;
    else if(dato == 1)  salida = 0x79;
    else if(dato == 2)  salida = 0x24;
    else if(dato == 3)  salida = 0x30;
    else if(dato == 4)  salida = 0x19;
    else if(dato == 5)  salida = 0x12;
    else if(dato == 6)  salida = 0x02;
    else if(dato == 7)  salida = 0x78;
    else if(dato == 8)  salida = 0x00;
    else if(dato == 9)  salida = 0x10;
                  else  salida = 0xFF;
    
    return salida;    
}
