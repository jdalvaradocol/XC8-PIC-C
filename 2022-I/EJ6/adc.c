
#include "adc.h"


void adc_Init(char ADFM, char ADCS, char ADNREF, char ADPREF)
{
    ADCON1bits.ADFM   = ADFM;   // Jutificacion de la conversion.
    ADCON1bits.ADCS   = ADCS;   // Frecuencia de conversion.
    ADCON1bits.ADNREF = ADNREF; // Voltaje de referencia VREF-.
    ADCON1bits.ADPREF = ADPREF; // Voltaje de referencia VREF-. 
}
int adc_Leer(char canal)
{
    int adc = 0;
    
    ADCON0bits.CHS = canal ; //Define el canal para relizar la conversion.
    
    ADCON0bits.ADON = ON;   // Encender el ADC.
    
    ADCON0bits.GO = ON;     // Habilitar o lanza la conversion.
    
    while(ADCON0bits.GO_nDONE == ON)
    {}
     
    // ADRESH 00000011 << 8 = 1100000000 
    // ADRESL                 0011111111
    
    adc = (ADRESH<<8) + ADRESL;

    return adc;
}

