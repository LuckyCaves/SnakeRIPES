#include "ripes_system.h"
#include <stdio.h>
#include <stdlib.h>

#define SW0 (0x01)

volatile unsigned int * initialPosition = (int*) LED_MATRIX_0_BASE;
volatile unsigned int * d_pad_up = (int*) D_PAD_0_UP;
volatile unsigned int * d_pad_do = (int*) D_PAD_0_DOWN;
volatile unsigned int * d_pad_le = (int*) D_PAD_0_LEFT;
volatile unsigned int * d_pad_ri = (int*) D_PAD_0_RIGHT;
volatile unsigned int * switch_base = (int*) SWITCHES_0_BASE;

const volatile unsigned int * TOP = (int *) LED_MATRIX_0_BASE;
const volatile unsigned int * BOTTOM = (int *) LED_MATRIX_0_BASE + (LED_MATRIX_0_SIZE / 4);
volatile unsigned int * applePosition = 0;
volatile unsigned int * snake[100]; 

#define MULTIPLIER 1103515245 
#define INCREMENT 12345 
#define MODULUS 2147483648 
unsigned int seed = 1;

void clean()
{
    volatile unsigned int * led = (int*) LED_MATRIX_0_BASE; // ir al primer led
    for(int i = 0; i < (LED_MATRIX_0_SIZE)/4; i++)
    {
        *led = 0x00; // apagar el led
        led++; // siguiente led
    }
}

void printSquare(volatile unsigned int* led, int color)
{

    *led = color;
    led--;
    *led = color;
    led -= LED_MATRIX_0_WIDTH;
    *led = color;
    led++;
    *led = color;
    led -= LED_MATRIX_0_WIDTH;

}

int isInside(volatile unsigned int* snake)
{
    int posIndex = snake - (volatile unsigned int * ) LED_MATRIX_0_BASE;
    int x = posIndex % LED_MATRIX_0_WIDTH;
    int y = posIndex / LED_MATRIX_0_WIDTH;

    return x == 0 || x == LED_MATRIX_0_WIDTH || y == 0 || y == LED_MATRIX_0_HEIGHT;
}

unsigned int lcg_rand() {
    seed = (MULTIPLIER * seed + INCREMENT) % MODULUS;
    return seed;
}

volatile unsigned int * generateApplePosition()
{
    return (int *) ((0 + lcg_rand() % (2500 - 0 + 1)) + 0xf0000014);
}

void drawSnake(int size, int speed)
{

    for(int i = size; i > 0; i--)
    {
        snake[i] = snake[i - 1];
        printSquare(snake[i], 0xFFD700);
    }
    snake[0] += speed;
    printSquare(snake[0], 0xFFD700);

}

void main()
{
    clean();

    int size = 0;
    int counter = 0;

    snake[size] = initialPosition;

    int speed = 1;

    snake[size] += 10;
    snake[size] += 500;

    while(1)
    {
        
        if(*d_pad_up == 1 && speed != LED_MATRIX_0_WIDTH)
            speed = -LED_MATRIX_0_WIDTH;
        if(*d_pad_do == 1 && speed != -LED_MATRIX_0_WIDTH)
            speed = LED_MATRIX_0_WIDTH;
        if(*d_pad_le == 1 && speed != 1)
            speed = -1;
        if(*d_pad_ri == 1 && speed != -1)
            speed = 1;

        printSquare(snake[size], 0x00);
        drawSnake(size, speed);

        if(0x01 & *switch_base || isInside(snake[0]))
        {
            for(int i = 0; i < size; i++)
            {
                snake[i] = 0;
            }
            clean();
            size = 0;
            snake[0] = initialPosition;
            snake[0] += 10;
            snake[0] += 500;
            speed = 1;
            counter = 0;
        }

        for(int i=0; i < 500; i++); // delay
        counter++;
        if(counter >= 10)
        {
            counter = 0;
            size++;
            snake[size] = snake[size - 1];
        }
    } 
}