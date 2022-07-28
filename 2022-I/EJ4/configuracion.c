/*
 * File:   configuracion.c
 * Author: josed
 *
 * Created on 19 de julio de 2022, 02:17 PM
 */


#include <xc.h>
#include "configuracion.h"


void oscilador(unsigned FREC)
{
    // Configuracion del Reloj interno 
    
    // PLL = OFF
    OSCCONbits.SPLLEN   = 0;
    
    // SCS = 10 OSC INTERNO
    OSCCONbits.SCS      = 2;

    // IRCF = FREC
    OSCCONbits.IRCF     = FREC;
    
    OSCSTAT = 0x00;
    OSCTUNE = 0x00;
    
}

void configuracion(void) 
{
  // Inicio de configuracion del uC
    
    oscilador(FRE_16MHz);

    // Configurar el puerto A como entrada.
    // 0 Salida
    // 1 entrada
    
    TRISAbits.TRISA7 = PIN_IN; 
    TRISAbits.TRISA6 = PIN_IN; 
    TRISAbits.TRISA5 = PIN_IN; 
    TRISAbits.TRISA4 = PIN_IN; 
    TRISAbits.TRISA3 = PIN_IN; 
    TRISAbits.TRISA2 = PIN_IN; 
    TRISAbits.TRISA1 = PIN_IN; 
    TRISAbits.TRISA0 = PIN_IN; 
    
    LATA   = DISABLE;
    ANSELA = DISABLE;
    WPUA   = DISABLE;
    
    // Configurar el puerto B como salida.
    // 0 Salida
    // 1 entrada
    
    TRISBbits.TRISB7 = PIN_OUT; 
    TRISBbits.TRISB6 = PIN_OUT; 
    TRISBbits.TRISB5 = PIN_OUT; 
    TRISBbits.TRISB4 = PIN_OUT; 
    TRISBbits.TRISB3 = PIN_OUT; 
    TRISBbits.TRISB2 = PIN_OUT; 
    TRISBbits.TRISB1 = PIN_OUT; 
    TRISBbits.TRISB0 = PIN_OUT; 
    
    LATB   = DISABLE;
    ANSELB = DISABLE;
    WPUB   = DISABLE;
    
    // Configurar el puerto C como salida.
    // 0 Salida
    // 1 entrada
    
    TRISCbits.TRISC7 = PIN_OUT; 
    TRISCbits.TRISC6 = PIN_OUT; 
    TRISCbits.TRISC5 = PIN_OUT; 
    TRISCbits.TRISC4 = PIN_OUT; 
    TRISCbits.TRISC3 = PIN_OUT; 
    TRISCbits.TRISC2 = PIN_OUT; 
    TRISCbits.TRISC1 = PIN_OUT; 
    TRISCbits.TRISC0 = PIN_OUT;     
    
    LATC    = DISABLE;
    ANSELC  = DISABLE;
    WPUC    = DISABLE;
    
    // Configurar el puerto D como salida.
    // 0 Salida
    // 1 entrada
    
    TRISDbits.TRISD7 = PIN_OUT; 
    TRISDbits.TRISD6 = PIN_OUT; 
    TRISDbits.TRISD5 = PIN_OUT; 
    TRISDbits.TRISD4 = PIN_OUT; 
    TRISDbits.TRISD3 = PIN_OUT; 
    TRISDbits.TRISD2 = PIN_OUT; 
    TRISDbits.TRISD1 = PIN_OUT; 
    TRISDbits.TRISD0 = PIN_OUT; 

    LATD    = DISABLE;
    ANSELD  = DISABLE;
    WPUD    = DISABLE;

}

