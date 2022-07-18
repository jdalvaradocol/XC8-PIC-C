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

#define _XTAL_FREQ 16000000

// Rutina de interrupcion

int estado = 0;
int delay = 0;

void __interrupt()  isr(void)
{
    // Verifico si se activo una INT por IOC
    
    if (INTCONbits.IOCIF == 1)
    {
        
        if (IOCAFbits.IOCAF0 == 1)  // Verifico si se activo INT RA0
        {
            estado = 0;
            // Rutina de INT para RA0
            PORTBbits.RB0 ^= 0x01;
            IOCAFbits.IOCAF0 = 0;
        }
        if (IOCAFbits.IOCAF1 == 1)  // Verifico si se activo INT RA1
        {
            estado = 1;
            // Rutina de INT para RA1
            PORTBbits.RB1 ^= 0x01;
            IOCAFbits.IOCAF1 = 0;
        }
        if (IOCAFbits.IOCAF2 == 1)  // Verifico si se activo INT RA0
        {
            estado = 2;
            // Rutina de INT para RA2
            PORTBbits.RB2 ^= 0x01;
            IOCAFbits.IOCAF2 = 0;
        }          
        
        INTCONbits.IOCIF = 0;
    }

    // Verifico si se activo una INT por TMR0
    
    if(INTCONbits.TMR0IF == 1)
    {   
        
        TMR0 = 99;                  // TMR0 = 99 para 10 mS
        
        delay++;
        
        if (delay >= 20)
        {
            PORTBbits.RB3 ^= 0x01;
            delay = 0;
        }
        INTCONbits.TMR0IF = 0;
    }

}


// Prototipo de la funcion
unsigned char display(char dato);
void oscilador(void);

int main ()
{
    // Inicio de configuracion del uC
    
    oscilador();

    // Configurar el puerto A como entrada.
    // 0 Salida
    // 1 entrada
    
    TRISA   = 0xFF; 
    LATA    = 0x00;
    ANSELA  = 0x00;
    WPUA    = 0x00;
    
    // Configurar interrupciones IOC para RB0 y RB1
    
    IOCAPbits.IOCAP0 = 1;       // Habilita la INT para RA0 por flanco de subida
    IOCAPbits.IOCAP1 = 1;       // Habilita la INT para RA1 por flanco de subida
    IOCAPbits.IOCAP2 = 1;       // Habilita la INT para RA2 por flanco de subida
    
    // Configurar el puerto B como salida.
    // 0 Salida
    // 1 entrada
    
    TRISB   = 0x00; 
    LATB    = 0x00;
    ANSELB  = 0x00;
    WPUB    = 0x00;
    
    // Configurar el puerto C como salida.
    // 0 Salida
    // 1 entrada
    
    TRISC   = 0x00; 
    LATC    = 0x00;
    ANSELC  = 0x00;
    WPUC    = 0x00;
    
    // Configurar el puerto D como salida.
    // 0 Salida
    // 1 entrada
    
    TRISD   = 0x00; 
    LATD    = 0x00;
    ANSELD  = 0x00;
    WPUD    = 0x00;

    // Configuracion TMR0 Delay 16 ms
    
    OPTION_REGbits.TMR0CS = 0; // Feunte Clock interno
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 7; 
    
    //  Configuracion de las interrupciones 
    
    INTCONbits.TMR0IE = 1;  // Habilito las interrupciones de TMR0.
    INTCONbits.IOCIE = 1;   // Habilito las interrupciones de IOC.
    INTCONbits.GIE = 1;     // Habilito las interrupciones Goblales.
    
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

void oscilador(void)
{
    
    // Configuracion del Reloj interno 
    // PLL = OFF
    // IRCF = 1111 F = 8 MHz
    // SCS = 10 OSC INTERNO
    
    OSCCONbits.SPLLEN   = 0;
    OSCCONbits.IRCF     = 15;
    OSCCONbits.SCS      = 2;
    
    OSCSTAT = 0x00;
    OSCTUNE = 0x00;
    
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