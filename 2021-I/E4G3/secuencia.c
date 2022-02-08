

#include "secuencia.h"

void secuencia_leds(volatile unsigned char *puerto)
{
    *puerto = 0xC3;
    __delay_ms(300);
    *puerto = 0x3C;
    __delay_ms(300);   
}