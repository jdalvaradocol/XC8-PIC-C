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

#define     display_sal     PORTD
#define     display_hab     PORTC

/*
 * 
 */

// prototipo de la funcion 

unsigned char  display(int dato);
unsigned char  visualizacion(int dato);

int main() 
{
    //Configuracion de los puertos.
    
    //Puerto C y D como salida.
    TRISC = 0x00;
    TRISD = 0x00;        

    while(true)
    {
        for (int i = 0;i < 1000; i++)
        {
            visualizacion(i);        
        }
    }
    
    return (EXIT_SUCCESS);
}

unsigned char display(int dato)
{
    unsigned char salida = 0;
    
         if(dato == 0)  salida = 0xBF;
    else if(dato == 1)  salida = 0x86;
    else if(dato == 2)  salida = 0xDB;
    else if(dato == 3)  salida = 0xCF;
    else if(dato == 4)  salida = 0xE6;
    else if(dato == 5)  salida = 0xED;
    else if(dato == 6)  salida = 0xFD;
    else if(dato == 7)  salida = 0x87;
    else if(dato == 8)  salida = 0xFF;
    else if(dato == 9)  salida = 0xEF;
                  else  salida = 0x00;
    
    return salida;    
}

unsigned char  visualizacion(int dato)
{       
    int unidadamil  = 0;
    int centena     = 0;
    int decena      = 0;
    int unidad      = 0; 
 
// modulo (%)    
// 1234 / 10 = 123
// a = 1234 / 1000 = 1
// b = ((1234) / 100)) - (a*10)  =  2
// c = (1234 / 10) - (a*100) - (b*10) =  3
// d = (1234) - (a*1000)-(b*100)-(c*10) =  4

    unidadamil = dato / 1000;
    centena = (dato/100) - (unidadamil*10);
    decena  = (dato/10) - (unidadamil*100) - (centena*10);
    unidad =  (dato) - (unidadamil*1000)-(centena*100)-(decena*10);
    
    for(int i = 0; i < 100 ;i++)
    {
        display_sal =  display(unidadamil);   
        display_hab = 0x08;
        __delay_ms(2);

        display_sal =  display(centena);   
        display_hab = 0x04;
        __delay_ms(2);

        display_sal =  display(decena);   
        display_hab = 0x02;
        __delay_ms(2);

        display_sal =  display(unidad);   
        display_hab = 0x01;
        __delay_ms(2);
    }
    
    return 0;       
    
}