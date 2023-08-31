#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct{
    int a;
    double b;
}typedef a_t;

int main(){
    a_t** a = (a_t**)malloc(4*sizeof(a_t*));
    for(int i=0; i<4; i++){
        a[i] = (a_t*)malloc(sizeof(a_t)*3);
    }
    a[0][0].a = 10;


    printf("sizeof a: %li\n", sizeof(a));
    printf("%i\n", a[0][0].a);
    
    for(int i=0; i<4; i++){
        free(a[i]);
    }
    free(a);
    printf("\n memory is freed\n");

}