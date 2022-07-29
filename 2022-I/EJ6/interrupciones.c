/*
 * File:   interrupciones.c
 * Author: josed
 *
 * Created on 19 de julio de 2022, 02:51 PM
 */


#include <xc.h>
#include "interrupciones.h"

extern int Tecla = 0;

void __interrupt()  isr(void)
{
    static unsigned char N = 1;
    static int delay = 0;
    static int variable = -4;
    
    // Verifico si se activo una INT por IOC
    
    if (INTCONbits.IOCIF == INT_ON)
    {
        if (IOCBFbits.IOCBF4 == INT_ON)  // Verifico si se activo INT RB4
        {
            Tecla = variable + 1;
            IOCBFbits.IOCBF4 = INT_OFF;
        }
        if (IOCBFbits.IOCBF5 == INT_ON)  // Verifico si se activo INT RB5
        {
            Tecla = variable + 2;
            IOCBFbits.IOCBF5 = INT_OFF;
        }
        if (IOCBFbits.IOCBF6 == INT_ON)  // Verifico si se activo INT RB6
        {

            IOCBFbits.IOCBF6 = INT_OFF;
        }
        if (IOCBFbits.IOCBF7 == INT_ON)  // Verifico si se activo INT RB7
        {

            IOCBFbits.IOCBF7 = INT_OFF;
        }
        
        
        INTCONbits.IOCIF = INT_OFF;
    }
    // Verifico si se activo una INT por TMR0
    
    if(INTCONbits.TMR0IF == INT_ON)
    {   
        
        if(delay >= 5)
        {
            PORTDbits.RD0 ^= 0x01;
            delay = 0;
            
            variable = variable + 4;
            
            if (variable == 16)
            {
                variable = 0;
            }

            PORTB = N;
            N = N * 2;
            
            if(N == 16)
            {
                N = 1;
            }
            
            
        }
        else
        {
            delay++;
        }
      
        TMR0 = 107;                  // TMR0 = 99 para 10 mS
        INTCONbits.TMR0IF = INT_OFF;
    }

}

void init_interrupciones(void)
{
    // Configurar interrupciones IOC para PUERTO A
    
    //    HABILITAR = ON
    // DESHABILITAR = OFF

    // configuracion del IOC para el PORTA 
    
    IOCAPbits.IOCAP0 = OFF;       // INT para RA0 por flanco de subida
    IOCAPbits.IOCAP1 = OFF;       // INT para RA1 por flanco de subida
    IOCAPbits.IOCAP2 = OFF;       // INT para RA2 por flanco de subida
    IOCAPbits.IOCAP3 = OFF;       // INT para RA3 por flanco de subida
    IOCAPbits.IOCAP4 = OFF;       // INT para RA4 por flanco de subida
    IOCAPbits.IOCAP5 = OFF;       // INT para RA5 por flanco de subida
  
    IOCANbits.IOCAN0 = OFF;       // INT para RA0 por flanco de bajada
    IOCANbits.IOCAN1 = OFF;       // INT para RA1 por flanco de bajada
    IOCANbits.IOCAN2 = OFF;       // INT para RA2 por flanco de bajada
    IOCANbits.IOCAN3 = OFF;       // INT para RA3 por flanco de bajada
    IOCANbits.IOCAN4 = OFF;       // INT para RA4 por flanco de bajada
    IOCANbits.IOCAN5 = OFF;       // INT para RA5 por flanco de bajada
  
    // configuracion del IOC para el PORTB 
    
    IOCBPbits.IOCBP0 = OFF;       // INT para RB0 por flanco de subida
    IOCBPbits.IOCBP1 = OFF;       // INT para RB1 por flanco de subida
    IOCBPbits.IOCBP2 = OFF;       // INT para RB2 por flanco de subida
    IOCBPbits.IOCBP3 = OFF;       // INT para RB3 por flanco de subida
    IOCBPbits.IOCBP4 =  ON;       // INT para RB4 por flanco de subida
    IOCBPbits.IOCBP5 =  ON;       // INT para RB5 por flanco de subida
    IOCBPbits.IOCBP6 =  ON;       // INT para RB6 por flanco de subida
    IOCBPbits.IOCBP7 =  ON;       // INT para RB7 por flanco de subida
  
    IOCBNbits.IOCBN0 = OFF;       // INT para RB0 por flanco de subida
    IOCBNbits.IOCBN1 = OFF;       // INT para RB1 por flanco de subida
    IOCBNbits.IOCBN2 = OFF;       // INT para RB2 por flanco de subida
    IOCBNbits.IOCBN3 = OFF;       // INT para RB3 por flanco de subida
    IOCBNbits.IOCBN4 = OFF;       // INT para RB4 por flanco de subida
    IOCBNbits.IOCBN5 = OFF;       // INT para RB5 por flanco de subida
    IOCBNbits.IOCBN6 = OFF;       // INT para RB6 por flanco de subida
    IOCBNbits.IOCBN7 = OFF;       // INT para RB7 por flanco de subida
    
    //  Configuracion de las interrupciones 
    
    INTCONbits.INTE   = OFF;     // Deshabilito las interrupciones de RB0.   
    INTCONbits.TMR0IE =  ON;     // Habilito las interrupciones de TMR0.
    INTCONbits.IOCIE  =  ON;     // Habilito las interrupciones de IOC.
    INTCONbits.GIE    =  ON;     // Habilito las interrupciones Goblales.
  
}