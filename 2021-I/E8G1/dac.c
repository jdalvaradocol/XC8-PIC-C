
#include "dac.h"

void DAC1_Init_OUT1(unsigned char DAC1PSS, unsigned char DAC1NSS)
{
    DAC1CON0bits.DACPSS  = DAC1PSS;
    DAC1CON0bits.DAC1NSS = DAC1NSS;
    
    DAC1CON0bits.DAC1OE1 = 1;
    DAC1CON0bits.DAC1OE2 = 0;   

    DAC1CON0bits.DACEN = 1;

}

void DAC1_escribir_OUT1(unsigned char DAC1R)
{
    DAC1CON1 = DAC1R;
}
