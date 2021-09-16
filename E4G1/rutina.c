

#include "rutina.h"

void rutina_4leds(volatile unsigned char * puerto)
{
    *puerto = 0x0F;
    __delay_ms(300);
        
    *puerto = 0xF0;
    __delay_ms(300);

}
