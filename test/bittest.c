#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define A 0b00000000
#define B 0b00000001
#define C 0b00000010
#define D 0b00000100
#define E 0b11111011

#define F 0b00001011


int main(){

    // uint8_t x;

    printf("%i\n", (E&0xF) == F);


    return 0;
}