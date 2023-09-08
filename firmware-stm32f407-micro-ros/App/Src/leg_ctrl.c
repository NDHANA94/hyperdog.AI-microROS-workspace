#include "leg_ctrl.h"


leg_t leg[4];

void init_legs()
{
    /* pointing leg[x].motor to corresponding legMotors */
    for(int i=0; i<4; i++){
        leg[i].motor[0] = &legMotor[i][0];
        leg[i].motor[1] = &legMotor[i][1];
        leg[i].motor[2] = &legMotor[i][2];

        leg[i].param.L1 = LEG_L1;
        leg[i].param.L2 = LEG_L2;
        leg[i].param.L3 = LEG_L3;

        leg[i].id = i;
    }
}

void fini_legs()
{
    for(int i=0; i<4; i++){
        for(int m=0; m<3; m++){
            free(leg[i].motor[m]);
        }
        free(leg[i].motor);
    }
    
}

/**
 * To solve Inverse Kinematics. Using the postion data of the `leg[x]`
 * instance, this calculates IK and saves results in `leg[x].nxt_states.joint_ang`.
 * \attention Before using this, make sure to update 
 * the `leg[x].nxt_state.position`.
 * \param *leg pointer to a leg instance to solve inverse kinematics (&leg[x])
 */
void solve_ik(leg_t* leg)
{
    hyperdog_uros_interfaces__msg__Vector3 p_ef = leg->nxt_states.position;
    float th0=0, th1=0, th2=0;
    /* hip_roll joint angle - th0 */
    float _r_yz = sqrtf(powf(p_ef.y, 2) + powf(p_ef.z, 2));
    float _sin_th0_plus_alpha = leg->param.L1/_r_yz;
    float _cos_th0_plus_alpha = sqrtf(1 - powf(_sin_th0_plus_alpha, 2));
    th0 = atan2f(_sin_th0_plus_alpha, _cos_th0_plus_alpha) - atan2f(p_ef.y, -p_ef.z);

    /* knee joint angle - th2 */
    float _cos_th2 = (powf(p_ef.x, 2) + powf(p_ef.y, 2) + powf(p_ef.z, 2) 
    - powf(leg->param.L1, 2) - powf(leg->param.L2, 2) - powf(leg->param.L3, 2))
    / (2 * leg->param.L2 * leg->param.L3);
    float _sin_th2 = sqrtf(1 - powf(_cos_th2,2));
    th2 = atan2f(_sin_th2, _cos_th2);

    /* hip_pitch joint angle - th1 */
    float _a = leg->param.L3 * sinf(th2);
    float _b = leg->param.L2 + leg->param.L3 * cosf(th2);
    float _c = sqrtf(powf(_a,2) + powf(_b,2));
    float _beta = atan2f(_b, _a);
    float _sin_th2_minus_beta = p_ef.x/_c;
    float _cos_th2_minus_beta = sqrtf(1 - powf(p_ef.x/_c, 2));
    float _th2_minus_beta = atan2f(_sin_th2_minus_beta, _cos_th2_minus_beta);
    th1 = _th2_minus_beta + _beta;

    if(isinf(th0) || isinf(th1) || isinf(th2) ||
        __isnanf(th0) || __isnanf(th1) || __isnanf(th2)) {goto singularity;}
    else {goto ok;}

    singularity:
        leg->nxt_states.error_code |= LEG_ERROR_SING;


    ok:
        leg->nxt_states.error_code &= ~LEG_ERROR_SING;
        leg->nxt_states.joint_ang[0] = th0;
        leg->nxt_states.joint_ang[1] = th1;
        leg->nxt_states.joint_ang[2] = th2;
}