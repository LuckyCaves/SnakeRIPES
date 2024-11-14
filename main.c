#include "ripes_system.h"
#include <stdio.h>
#include <stdlib.h>

#define SW0 (0x01)

volatile unsigned int * led_base = (int*) LED_MATRIX_0_BASE;
volatile unsigned int * d_pad_up = (int*) D_PAD_0_UP;
volatile unsigned int * d_pad_do = (int*) D_PAD_0_DOWN;
volatile unsigned int * d_pad_le = (int*) D_PAD_0_LEFT;
volatile unsigned int * d_pad_ri = (int*) D_PAD_0_RIGHT;
volatile unsigned int * switch_base = (int*) SWITCHES_0_BASE;

void clean(unsigned int mask)
{

    mask = SW0 & *switch_base; // aislar el valor del sw0
    if(mask == SW0)
    {
        led_base = (int*) LED_MATRIX_0_BASE; // ir al primer led
        for(int i = 0; i < (LED_MATRIX_0_SIZE)/4; i++)
        {
            *led_base = 0x00; // apagar el led
            led_base++;       // siguiente led
        }
    }

}

void main()
{   
    unsigned int mask = 0;
    volatile unsigned int * tmp;
    int speed = 0;

    while(1)
    {

        // srand(a);
        // int num = rand();
        // printf("%i\n", num);
        // a++;
        
        if(*d_pad_up == 1)
            speed = -LED_MATRIX_0_WIDTH;
            // led_base -= LED_MATRIX_0_WIDTH; // ir una fila arriba
        if(*d_pad_do == 1)
            speed = LED_MATRIX_0_WIDTH;
            // led_base += LED_MATRIX_0_WIDTH; // ir una fila abajo
        if(*d_pad_le == 1)
            speed = -1;
            // led_base -= 1;
        if(*d_pad_ri == 1)
            speed = 1;
            // led_base += 1;

        led_base += speed;
        *led_base = 0xFFD700;
        tmp = led_base;
        
        for(int i=0; i < 750; i++); // delay
        
        clean(mask);
        led_base = tmp;
    } 
}