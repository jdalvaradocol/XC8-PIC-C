

#include "adc.h"

void    ADC_Init(unsigned char ADPREF, unsigned char ADNREF, unsigned char ADFM, unsigned char FOSC)
{
    ADCON1bits.ADPREF   =   ADPREF;
    ADCON1bits.ADNREF   =   ADNREF;   
    ADCON1bits.ADFM     =   ADFM;  
    ADCON1bits.ADCS     =   FOSC;
}

 int    ADC_Lectura(unsigned char CHS)
 { 
     int result = 0;
     
     ADCON0bits.CHS = CHS;      // Sel CHS
     
     ADCON0bits.ADON = 1;       // ADC ON
     __delay_ms(1);
     
     ADCON0bits.GO = 1;         // Iniciar la conversion del ADC
     
     while(ADCON0bits.GO_nDONE)
     {
         // Esperamos que finalice la Conversion. 
     }
     
     ADCON0bits.ADON = 1;       // ADC ON
     
     // 11 --> 1100000000
     
     result = (ADRESH<<8) + ADRESL;
         
     return result;
 
 }
