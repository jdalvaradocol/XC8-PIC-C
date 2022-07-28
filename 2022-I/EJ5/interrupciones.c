/*
 * File:   interrupciones.c
 * Author: josed
 *
 * Created on 19 de julio de 2022, 02:51 PM
 */


#include <xc.h>
#include "interrupciones.h"


void __interrupt()  isr(void)
{
    static int delay = 0;
    // Verifico si se activo una INT por IOC
    
    if (INTCONbits.IOCIF == INT_ON)
    {}
        if (IOCAFbits.IOCAF0 == INT_ON)  // Verifico si se activo INT RA0
        {
            // Rutina de INT para RA0
            PORTBbits.RB0 ^= 0x01;
            
            IOCAFbits.IOCAF0 = INT_OFF;
        }
        if (IOCAFbits.IOCAF1 == INT_ON)  // Verifico si se activo INT RA1
        {
            // Rutina de INT para RA1
            PORTBbits.RB1 ^= 0x01;
            IOCAFbits.IOCAF1 = INT_OFF;
        }
        if (IOCAFbits.IOCAF2 == INT_ON)  // Verifico si se activo INT RA0
        {
            // Rutina de INT para RA2
            PORTBbits.RB2 ^= 0x01;
            IOCAFbits.IOCAF2 = INT_OFF;
        }          
        
        INTCONbits.IOCIF = INT_OFF;
    
    // Verifico si se activo una INT por TMR0
    
    if(INTCONbits.TMR0IF == INT_ON)
    {   
        
        if(delay > 20)
        {
            PORTDbits.RD0 ^= 0x01;
            delay = 0;
        }
        else
        {
            delay++;
        }
        
        
        TMR0 = 99;                  // TMR0 = 99 para 10 mS
        INTCONbits.TMR0IF = INT_OFF;
    }

}

void init_interrupciones(void)
{
    // Configurar interrupciones IOC para PUERTO A
    
    //    HABILITAR = ON
    // DESHABILITAR = OFF
        
    IOCAPbits.IOCAP0 =  ON;       // INT para RA0 por flanco de subida
    IOCAPbits.IOCAP1 =  ON;       // INT para RA1 por flanco de subida
    IOCAPbits.IOCAP2 =  ON;       // INT para RA2 por flanco de subida
    IOCAPbits.IOCAP3 = OFF;       // INT para RA3 por flanco de subida
    IOCAPbits.IOCAP4 = OFF;       // INT para RA4 por flanco de subida
    IOCAPbits.IOCAP5 = OFF;       // INT para RA5 por flanco de subida
  
    IOCANbits.IOCAN0 = OFF;       // INT para RA0 por flanco de bajada
    IOCANbits.IOCAN1 = OFF;       // INT para RA1 por flanco de bajada
    IOCANbits.IOCAN2 = OFF;       // INT para RA2 por flanco de bajada
    IOCANbits.IOCAN3 = OFF;       // INT para RA3 por flanco de bajada
    IOCANbits.IOCAN4 = OFF;       // INT para RA4 por flanco de bajada
    IOCANbits.IOCAN5 = OFF;       // INT para RA5 por flanco de bajada
  
    
    //  Configuracion de las interrupciones 
    
    INTCONbits.INTE   = OFF;     // Deshabilito las interrupciones de RB0.   
    INTCONbits.TMR0IE =  ON;     // Habilito las interrupciones de TMR0.
    INTCONbits.IOCIE  =  ON;     // Habilito las interrupciones de IOC.
    INTCONbits.GIE    =  ON;     // Habilito las interrupciones Goblales.
  
}