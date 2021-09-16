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

#define     display_seg     PORTD    
#define     display_hab     PORTC
#define     entrada_ds      PORTA

// Declaracion de prototipo de las funciones.

unsigned char display(int numero);
void visualizacion(int dato);

int main()
{
    // configuracion de puertos.

    // Configurar PORTA 
    
    TRISA = 0x3F;
    ADCON1 = 0x07;

    // Configurar PORTC y PORTD salida
    
    TRISC = 0;
    TRISD = 0;        
        
    while(true)
    {
        for(int i= 0;i < entrada_ds; i++)
        {
            visualizacion(i); 
        }
    }
    
    return (EXIT_SUCCESS);
}

unsigned char display(int numero)
{
    unsigned char salida_display;
    
          if(numero == 0)   salida_display = 0xBF;
    else if (numero == 1)   salida_display = 0x86;
    else if (numero == 2)   salida_display = 0xDB;
    else if (numero == 3)   salida_display = 0xCF;
    else if (numero == 4)   salida_display = 0xE6;
    else if (numero == 5)   salida_display = 0xED;
    else if (numero == 6)   salida_display = 0xFD;
    else if (numero == 7)   salida_display = 0x87;
    else if (numero == 8)   salida_display = 0xFF;
    else if (numero == 9)   salida_display = 0xEF;
    else                    salida_display = 0x00;

    return salida_display;
    
}

void visualizacion(int dato)
{
// (int) 1234
// int a = 1
// int b = 2
// int c = 3
// int d = 4
 
// a = 1234 / 1000                           = 1   
// b = (1234 - (a*1000) / 100)               = 2
// c = ((1234 - (a*1000) - (b*100)) / 10)    = 3
// d = (1234 - (a*1000) - (b*100) - (c*10) ) = 4
    
    int um=0,cen=0,dec=0,uni=0;
    
    um = dato / 1000;
    cen = (dato - (um*1000)) / 100;
    dec = (dato - (um*1000) - (cen*100)) / 10;
    uni = (dato - (um*1000) - (cen*100)) - (dec*10);
    
    // Realizar el procedimiento anterior con la operacion modulo (%) 
    
    for(int i=0;i < 50; i++)
    {
        display_seg = display(uni);    
        display_hab = 0x01;
        __delay_ms(3);
        display_seg = display(dec);    
        display_hab = 0x02;
        __delay_ms(3);
        display_seg = display(cen);    
        display_hab = 0x04;
        __delay_ms(3);
        display_seg = display(um);    
        display_hab = 0x08;
        __delay_ms(3);
    }
}