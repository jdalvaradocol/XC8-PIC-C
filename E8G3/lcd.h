#ifndef __lcd_H
#define __lcd_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ 1000000

#define LCD_RD7     PORTCbits.RC3       // D7
#define TRISRD7     TRISCbits.TRISC3

#define LCD_RD6     PORTCbits.RC2       // D6
#define TRISRD6     TRISCbits.TRISC2

#define LCD_RD5     PORTCbits.RC1       // D5
#define TRISRD5     TRISCbits.TRISC1

#define LCD_RD4     PORTCbits.RC0       // D4
#define TRISRD4     TRISCbits.TRISC0

#define LCD_RS      PORTCbits.RC4       // RS
#define TRISRS      TRISCbits.TRISC4

#define LCD_EN      PORTCbits.RC5       // EN
#define TRISEN      TRISCbits.TRISC5

//#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000)))

//comandos disponibles
#define      LCD_FIRST_ROW           128
#define      LCD_SECOND_ROW          192
#define      LCD_THIRD_ROW           148
#define      LCD_FOURTH_ROW          212
#define      LCD_CLEAR               1
#define      LCD_RETURN_HOME         2
#define      LCD_CURSOR_OFF          12
#define      LCD_UNDERLINE_ON        14
#define      LCD_BLINK_CURSOR_ON     15
#define      LCD_MOVE_CURSOR_LEFT    16
#define      LCD_MOVE_CURSOR_RIGHT   20
#define      LCD_TURN_OFF            0
#define      LCD_TURN_ON             8
#define      LCD_SHIFT_LEFT          24
#define      LCD_SHIFT_RIGHT         28

void Lcd_Init(void);
void Lcd_Out(unsigned char y, unsigned char x, const char *buffer);
void Lcd_Out2(unsigned char y, unsigned char x, char *buffer);
void Lcd_Chr_CP(unsigned char data);
void Lcd_Cmd(unsigned char data);

#endif
























