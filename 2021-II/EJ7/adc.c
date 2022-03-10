/*
 * File:   adc.c
 * Author: josed
 *
 * Created on 10 de marzo de 2022, 12:15 PM
 */

#include <xc.h>
#include "adc.h"

void ADC_Init(unsigned char ADPREF, unsigned char ADNREF, unsigned char ADFM, unsigned char ADCS)
{    
    ADCON1bits.ADPREF = ADPREF; // VREF +
    ADCON1bits.ADNREF = ADNREF; // VREF -
    ADCON1bits.ADFM   = ADFM;   // Justificacaion.
    ADCON1bits.ADCS   = ADCS;   // Frecuencia.
}

int ADC_leer(unsigned char CH)
{
    int resultado = 0;
    
    ADCON0bits.CHS = CH; // seleccionando canal de conversion.  
    
    ADCON0bits.ADON = 1;    // ADC ON
    __delay_ms(1);
    
    ADCON0bits.GO = 1;      // Lanzar la conversion.
    
    while(ADCON0bits.GO_nDONE)
    {
        // Espera que finalice la conversion.    
    }
    
    ADCON0bits.ADON = 0;    // ADC OFF
    
    resultado = (ADRESH<<8) + (ADRESL);
       
    return  resultado;  

}
