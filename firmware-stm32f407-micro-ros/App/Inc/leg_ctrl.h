#ifndef LEG_CTRL_H__
#define LEG_CTRL_H__

#ifdef __cplusplus
extern "C"{
#endif
#include "math.h"

#include "leg_motors.h"
#include "hyperdog_uros_interfaces/msg/legs_cmd.h"
#include "hyperdog_uros_interfaces/msg/leg_cmd.h"
#include "hyperdog_uros_interfaces/msg/legs_states.h"
#include "hyperdog_uros_interfaces/msg/leg_states.h"
#include "hyperdog_uros_interfaces/msg/vector3.h"


#define LEG_L1                          0.1;    /*!< in meters */
#define LEG_L2                          0.2;    /*!< in meters */
#define LEG_L3                          0.2;    /*!< in meters */

#define LEG_ERROR_NONE                  0b00000000
#define LEG_ERROR_MOTOR_HR              0b00000001  /*!< hip_roll motor error       */
#define LEG_ERROR_MOTOR_HP              0b00000010  /*!< hip_pitch motor error      */
#define LEG_ERROR_MOTOR_K               0b00000100  /*!< knee motor error           */
#define LEG_ERROR_SING                  0b00001000  /*!< singularity error          */
#define LEG_ERROR_ROL                   0b00010000  /*!< Reaction force if over-loaded         */



enum legId{
    FR = 0,
    FL = 1,
    RR = 2,
    RL = 3
};

struct{
    float L1;
    float L2;
    float L3;
}typedef legParam_t;




struct{
    /**
     * \brief Current states of the leg: use as the feedback of the leg
     * \param is_contacted `true` if the foot contacted with the ground, otherwise `false`. [`bool`]
     * \param error_code    to indicate the error state. [`uint8`]
     * \param position currunt position of the end effector. [`Vector3`]
     * \param velocity currunt velocity of the end effector. [`Vector3`]
     * \param applied_force currunt applied force at the end effector. [`Vector3`]
     * \param reaction_force currunt reaction force at the end effector. [`Vector3`]
     * \param stiffness_ratio [`Vector3`]
     * \param damping_ratio [`Vector3`]                                 
     * \param joint_ang[3]  `joint_ang[0]=hip_roll`, `joint_ang[1]=hip_pitch`, `joint_ang[2]=knee`*/
    hyperdog_uros_interfaces__msg__LegStates                  cur_states;
    /**
     * \brief Next states of the leg (or desire leg state): this states will be used to execute the next process
     * \param position Next position of the end effector. [`Vector3`]
     * \param velocity Next velocity of the end effector. [`Vector3`]
     * \param applied_force Next applied force at the end effector. [`Vector3`]
     * \param stiffness_ratio [`Vector3`]
     * \param damping_ratio [`Vector3`]                                
     * \param joint_ang[3]  `joint_ang[0]=hip_roll`, `joint_ang[1]=hip_pitch`, `joint_ang[2]=knee`*/
    hyperdog_uros_interfaces__msg__LegStates                  nxt_states;
    /**
     * \brief Previous states of the leg:
     * \param is_contacted N/A
     * \param error_code    N/A
     * \param position previous position of the end effector. [`Vector3`]
     * \param velocity previous velocity of the end effector. [`Vector3`]
     * \param applied_force previous applied force at the end effector. [`Vector3`]
     * \param reaction_force previous reaction force at the end effector. [`Vector3`]
     * \param stiffness_ratio [`Vector3`]
     * \param damping_ratio [`Vector3`]                                 
     * \param joint_ang[3]  `joint_ang[0]=hip_roll`, `joint_ang[1]=hip_pitch`, `joint_ang[2]=knee`*/
    hyperdog_uros_interfaces__msg__LegStates                  prv_states;
    /**
     * \brief Control commands:
     * \param position desire position of the end effector [`Vector3`]
     * \param velocity desire velocity of the end effector. [`Vector3`]
     * \param stiffness_ratio desire stiffness [`Vector3`]
     * \param damping_ratio desire damping [`Vector3`]                  */
    hyperdog_uros_interfaces__msg__LegCmd                             cmd;
    /**
     * Joint motors
     * \param m[0] hip_roll joint motor
     * \param m[1] hip_pitch joint motor
     * \param m[2] knee joint motor                     */
    LegMotor_TypeDef**                             motor;
    /** parameters of the leg 
     * \param L1 
     * \param L2 
     * \param L3                                        */
    legParam_t                                     param;
    /**
     * ID of the leg; `0=FR`, `1=FL`, `2=RR`, `3=RL`
     */
    enum legId                                        id;

}typedef leg_t;

extern leg_t leg[4];

void init_legs();
void fini_legs();
void solve_ik(leg_t* leg);

#ifdef __cplusplus
}
#endif

#endif