#include <stdio.h>

// Define the constants for the LCG
#define MULTIPLIER 1103515245
#define INCREMENT 12345
#define MODULUS 2147483648

// Seed value
unsigned int seed = 1;

// Function to generate a random number
unsigned int lcg_rand() {
    seed = (MULTIPLIER * seed + INCREMENT) % MODULUS;
    return seed;
}

volatile unsigned int * random_in_range() 
{ 
    return (int *) ((0 + lcg_rand() % (2500 - 0 + 1)) + 0xf0000014);  
}

int main() {
    // Generate and print a random number
    volatile unsigned int * random_number = random_in_range();
    printf("Random Number: %x\n", random_number);
    random_number = random_in_range();
    printf("Random Number: %x\n", random_number);

    return 0;
}
