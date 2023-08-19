#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


enum MotorError {
    NO_ERROR        = 0b0000,
    OFFLINE         = 0b0001,
    OUT_OF_RANGE    = 0b0010,
    OVER_HEATED     = 0b0100,
    OVER_CURRENT    = 0b1000
};

void print_err(enum MotorError mErr){
    switch (mErr)
    {
    case 0b0000:
        printf("motor has no error\n");
        break;
    case 0b0001:
        printf("motor is offline\n");
        break;
    case 0b0010:
        printf("motor is out of range\n");
        break;
    case 0b0100:
        printf("motor is over heated\n");
        break;
    case 0b1000:
        printf("motor takes over current\n");
        break;
    
    default:
        break;
    }
}

int main(){

    // enum type to numbers
    enum MotorError mError;
    mError = OVER_CURRENT;
    printf("motor error: %i\n", mError);
    print_err(mError);

    // numbers to enum
    int err = 0b0100;
    mError = (enum MotorError)err;
    printf("motor error: %i\n", mError);
    print_err(mError);

    return 0;
}