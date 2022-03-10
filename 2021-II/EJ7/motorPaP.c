/*
 * File:   motorPaP.c
 * Author: josed
 *
 * Created on 10 de marzo de 2022, 12:50 PM
 */


#include <xc.h>
#include <math.h>
#include "motorPaP.h"

void motorPaP(int dirreccion, int velocidad, unsigned char * PORTX)
{
    if(dirreccion == DERECHA)
    {
        for(int i=0; i < 4 ; i++)
        {
            *PORTX =  (unsigned char) pow(2,i);
            
            for(int j=0; j < velocidad ;j++)
            {
                __delay_ms(1);
            }
            
        }
    }
    else if(dirreccion == IZQUIERDA)
    {
        for(int i = 3; i > -1 ; i--)
        {
            *PORTX =  (unsigned char) pow(2,i);
            
            for(int j = 0;j < velocidad; j++)
            {
                __delay_ms(1);
            }
            
        }
    }
    
}
