#include <stdio.h>
#include <stdlib.h>


struct{
    int id;
    double  position;
    double  velocity;
    double  kp;
    double  kd;
    double  iff;
}typedef motor_t;

#define NUM_OF_LEGS             4 
#define NUM_OF_LEG_JOINTS       3


void update_id(motor_t *m, int id){
    m->id = id;
}

int main()
{

    printf("motor_t size = %ld\n", sizeof(motor_t*));

    // legs 
    motor_t** m = (motor_t**)malloc (NUM_OF_LEGS * sizeof(motor_t*));
    // joint for each legs
    for (int i=0; i<NUM_OF_LEGS; i++){
        m[i] = (motor_t*)malloc(NUM_OF_LEG_JOINTS*sizeof(motor_t));
    }
    
    printf("m* size = %ld\n", sizeof(m));

    
    update_id(&m[0][0], 10);
    update_id(&m[1][1], 20);
    update_id(&m[2][2], 30);
    update_id(&m[3][3], 40);
    // m[0][0].id = 1;
    // m[1][0].id = 2;
    // m[2][0].id = 3;
    // m[3][0].id = 4;

    printf("motor ids: %i, %i, %i, %i \n", m[0][0].id, m[1][1].id, m[2][2].id, m[3][3].id);



    for(int i=0; i<4; i++){
        free(m[i]);
    }
    free(m);
    
    
    return 0;
}