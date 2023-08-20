#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define A 0b00000000
#define B 0b00000001
#define C 0b00000010
#define D 0b00000100
#define E 0b11111011

#define F 0b00001011

bool is_init(uint8_t a){
    return (a&F) == F;
}

int main(){

    // uint8_t x;
    uint8_t a = 0b01011001;
    printf("%i\n", is_init(a));


    return 0;
}