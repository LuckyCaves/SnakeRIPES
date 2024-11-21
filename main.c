#include "ripes_system.h"
#include <stdio.h>
#include <stdlib.h>

volatile unsigned int * initialPosition = (int*) LED_MATRIX_0_BASE;
volatile unsigned int * d_pad_up = (int*) D_PAD_0_UP;
volatile unsigned int * d_pad_do = (int*) D_PAD_0_DOWN;
volatile unsigned int * d_pad_le = (int*) D_PAD_0_LEFT;
volatile unsigned int * d_pad_ri = (int*) D_PAD_0_RIGHT;
volatile unsigned int * switch_base = (int*) SWITCHES_0_BASE;

const volatile unsigned int * TOP = (int *) LED_MATRIX_0_BASE;
const volatile unsigned int * BOTTOM = (int *) LED_MATRIX_0_BASE + (LED_MATRIX_0_SIZE / 4);
volatile unsigned int * snake[100];
volatile unsigned int * headPointer[2];
volatile unsigned int * position;


void clean()
{
    volatile unsigned int * led = (int*) LED_MATRIX_0_BASE; // ir al primer led
    for(int i = 0; i < (LED_MATRIX_0_SIZE)/4; i++)
    {
        *led = 0x00; // apagar el led
        led++; // siguiente led
    }
}

void printSquare(volatile unsigned int* led, unsigned int color)
{

    *led = color;
    led--;
    *led = color;
    led -= LED_MATRIX_0_WIDTH;
    *led = color;
    led++;
    *led = color;
}

int isInside(volatile unsigned int* pos)
{
    int posIndex = pos - (volatile unsigned int * ) LED_MATRIX_0_BASE;
    int x = posIndex % LED_MATRIX_0_WIDTH;
    int y = posIndex / LED_MATRIX_0_WIDTH;

    return x == 0 || x == LED_MATRIX_0_WIDTH || y == 0 || y == LED_MATRIX_0_HEIGHT;
}

void generateApple()
{

    int r = rand() % 5000;
    position = (int *) (r + 0xF0000014);

    printSquare(position, 0xFF5800);

}

void updateSnake(int size, int speed)
{

    for(int i = size; i > 0; i--)
        snake[i] = snake[i - 1];

    snake[0] += (speed * 2);

}

void updateHead(int speed)
{
    if(speed == -1)
    {
        headPointer[0] = snake[0] - 1;
        headPointer[1] = snake[0] - 1 - LED_MATRIX_0_WIDTH;
    }
    else if(speed == LED_MATRIX_0_WIDTH)
    {
        headPointer[0] = snake[0];
        headPointer[1] = snake[0] - 1;
    }
    else if(speed == -LED_MATRIX_0_WIDTH)
    {
        headPointer[0] = snake[0] - LED_MATRIX_0_WIDTH;
        headPointer[1] = snake[0] - 1 - LED_MATRIX_0_WIDTH;
    }
    else
    {
        headPointer[0] = snake[0];
        headPointer[1] = snake[0] - LED_MATRIX_0_WIDTH;
    }
    
}

void main()
{
    clean();

    int size = 0;
    int speed = 1;

    snake[0] = initialPosition;

    generateApple();

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
        updateSnake(size, speed);
        updateHead(speed);

        if(*headPointer[0] == 0xFFD700 || 0x01 & *switch_base || isInside(snake[0]))
        {
            for(int i = 0; i < size; i++)
            {
                snake[i] = 0;
            }
            clean();
            size = 0;
            speed = 1;
            snake[0] = initialPosition;
            snake[0] += 10;
            snake[0] += 500;
            generateApple();
        }
        else if(*headPointer[0] == 0xFF5800 || *headPointer[1] == 0xFF5800)
        {
            size++;
            snake[size] = snake[size - 1];
            printSquare(position, 0x00);
            generateApple();
        }

        printSquare(snake[0], 0xFFD700);
        for(int j = 0; j < 1750; j++);//delay
    }
}