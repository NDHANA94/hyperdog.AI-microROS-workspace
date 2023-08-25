#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define MOTOR_ENABLE_CMD         {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}
#define n_motors 12

typedef uint8_t  motor_status_t ;
typedef uint8_t  motor_errorcode_t;

struct{
    float min;
    float max;
}typedef range_t;

struct{
    range_t p;
    range_t v;
    range_t kp;
    range_t kd;
    range_t i_ff;
}typedef motor_param_t;

struct{
    range_t position; // to limit motor position 
    range_t velocity; // to limit motor velocity
    range_t current; // to limit motor intake current. If motor current exceed the limit, disable the motor or do safety control
}typedef motor_ctrl_limits_t;

struct {
    float p_des;
    float v_des;
    float kp;
    float kd;
    float iff;
}typedef motor_cmd_t;



struct{
    float position;
    float velocity;
    float current;
}typedef motor_current_states_t;

struct{
    uint8_t                 id;
    motor_param_t           params;
    motor_ctrl_limits_t     limit;
    motor_cmd_t             cmd;
    motor_current_states_t  states;
    motor_status_t          status;
}typedef motor_t;

motor_t* m;

enum MOTORS{
    FR_HIP,
    FR_THIGH,
    FR_CALF,
    FL_HIP,
    FL_THIGH,
    BR_HIP,
    BR_THIGH,
    BR_CALF,
    BL_HIP,
    BL_THIGH,
    BL_CALF
};

void Motor_setParams(int i, double pMax){ //, vMax, kpMax, kdMax, iffMax
    m[i].params.p.max = pMax;
}



int main(){

    extern motor_t* m;
    m = (motor_t*) malloc(n_motors*sizeof(motor_t));

    enum MOTORS motors_;
    
    Motor_setParams(0, 102);

    Motor_setParams(1, 1102);


    printf("motor id: %f\n", m[0].params.p.max);
    printf("motor id: %f\n", m[1].params.p.max);
    printf("motor id: %i\n", m[1].status);

    uint8_t enble_cmd[8] = MOTOR_ENABLE_CMD;
    printf("motor enable cmd: %i\n", enble_cmd[0]);

    printf("size of enum MOTORS: %li\n", sizeof(motors_));

    uint8_t temp[8];
    printf("%li\n", sizeof(temp));

    return 0;
}