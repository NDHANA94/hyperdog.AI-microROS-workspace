/**
 * Author: Nipun Dhananjaya Weerakkodi  (nipun.dhananjaya@gmail.com)
 * Last update: 02.09.2023
 * 
===========================================================================================
MIT License                                                                               |
                                                                                          |
Copyright (c) 2023 Nipun Dhananjaya Weerakkodi                                            |
                                                                                          |
Permission is hereby granted, free of charge, to any person obtaining a copy              |
of this software and associated documentation files (the "Software"), to deal             |
in the Software without restriction, including without limitation the rights              |
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell                 |
copies of the Software, and to permit persons to whom the Software is                     |
furnished to do so, subject to the following conditions:                                  |
                                                                                          |
The above copyright notice and this permission notice shall be included in all            |
copies or substantial portions of the Software.                                           |
                                                                                          |
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR                |
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                  |
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE               |
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                    |
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,             |
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE             |
SOFTWARE.                                                                                 |
                                                                                          |
==========================================================================================*/

#include "hyperdog_ctrl_legs/initLegMotorsMsg_config.hpp"

auto msg = hyperdog_uros_interfaces::msg::InitLegMotors();
hyperdog_uros_interfaces::msg::InitLegMotors get_initLegMotors_reqMsg(){
    /* FR Leg joint motors */
    msg.fr_hip_roll.params.can_id           =  1;
    msg.fr_hip_roll.params.position.min     = -12.5;
    msg.fr_hip_roll.params.position.max     =  12.5;
    msg.fr_hip_roll.params.velocity.min     = -65.0;
    msg.fr_hip_roll.params.velocity.max     =  65.0;
    msg.fr_hip_roll.params.kp.min           =  0.0;
    msg.fr_hip_roll.params.kp.max           =  500.0;
    msg.fr_hip_roll.params.kd.min           =  0.0;
    msg.fr_hip_roll.params.kd.max           =  5.0;
    msg.fr_hip_roll.params.i_ff.min         = -18.0;
    msg.fr_hip_roll.params.i_ff.max         =  18.0;
    msg.fr_hip_roll.ctrl_limits.position.min    = -1.5708; // rad // -90 deg
    msg.fr_hip_roll.ctrl_limits.position.max    =  1.5708; // rad //  90 deg
    msg.fr_hip_roll.ctrl_limits.velocity.min    = -1.0; // rad/s 
    msg.fr_hip_roll.ctrl_limits.velocity.max    =  1.0; // rad/s 
    msg.fr_hip_roll.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT; // A 
    msg.fr_hip_roll.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT; // A 

    msg.fr_hip_pitch.params.can_id           =  2;
    msg.fr_hip_pitch.params.position.min     = -12.5;
    msg.fr_hip_pitch.params.position.max     =  12.5;
    msg.fr_hip_pitch.params.velocity.min     = -65.0;
    msg.fr_hip_pitch.params.velocity.max     =  65.0;
    msg.fr_hip_pitch.params.kp.min           =  0.0;
    msg.fr_hip_pitch.params.kp.max           =  500.0;
    msg.fr_hip_pitch.params.kd.min           =  0.0;
    msg.fr_hip_pitch.params.kd.max           =  5.0;
    msg.fr_hip_pitch.params.i_ff.min         = -18.0;
    msg.fr_hip_pitch.params.i_ff.max         =  18.0;
    msg.fr_hip_pitch.ctrl_limits.position.min    = -3.14159;    // rad // -180 deg
    msg.fr_hip_pitch.ctrl_limits.position.max    =  3.14159;    // rad //  180 deg
    msg.fr_hip_pitch.ctrl_limits.velocity.min    = -1.0;        // rad/s 
    msg.fr_hip_pitch.ctrl_limits.velocity.max    =  1.0;        // rad/s 
    msg.fr_hip_pitch.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;       // A 
    msg.fr_hip_pitch.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;       // A 

    msg.fr_knee.params.can_id           =  3;
    msg.fr_knee.params.position.min     = -12.5;
    msg.fr_knee.params.position.max     =  12.5;
    msg.fr_knee.params.velocity.min     = -65.0;
    msg.fr_knee.params.velocity.max     =  65.0;
    msg.fr_knee.params.kp.min           =  0.0;
    msg.fr_knee.params.kp.max           =  500.0;
    msg.fr_knee.params.kd.min           =  0.0;
    msg.fr_knee.params.kd.max           =  5.0;
    msg.fr_knee.params.i_ff.min         = -18.0;
    msg.fr_knee.params.i_ff.max         =  18.0;
    msg.fr_knee.ctrl_limits.position.min    =  0.261799;    // rad // 15 deg
    msg.fr_knee.ctrl_limits.position.max    =  2.96706;     // rad // 170 deg
    msg.fr_knee.ctrl_limits.velocity.min    = -1.0;      // rad/s 
    msg.fr_knee.ctrl_limits.velocity.max    =  1.0;      // rad/s 
    msg.fr_knee.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;      // A 
    msg.fr_knee.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;      // A 

    /* FL Leg joint motors */
    msg.fl_hip_roll.params.can_id           =  4;
    msg.fl_hip_roll.params.position.min     = -12.5;
    msg.fl_hip_roll.params.position.max     =  12.5;
    msg.fl_hip_roll.params.velocity.min     = -65.0;
    msg.fl_hip_roll.params.velocity.max     =  65.0;
    msg.fl_hip_roll.params.kp.min           =  0.0;
    msg.fl_hip_roll.params.kp.max           =  500.0;
    msg.fl_hip_roll.params.kd.min           =  0.0;
    msg.fl_hip_roll.params.kd.max           =  5.0;
    msg.fl_hip_roll.params.i_ff.min         = -18.0;
    msg.fl_hip_roll.params.i_ff.max         =  18.0;
    msg.fl_hip_roll.ctrl_limits.position.min    = -1.5708; // rad // -90 deg
    msg.fl_hip_roll.ctrl_limits.position.max    =  1.5708; // rad //  90 deg
    msg.fl_hip_roll.ctrl_limits.velocity.min    = -1.0; // rad/s 
    msg.fl_hip_roll.ctrl_limits.velocity.max    =  1.0; // rad/s 
    msg.fl_hip_roll.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT; // A 
    msg.fl_hip_roll.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT; // A 

    msg.fl_hip_pitch.params.can_id           =  5;
    msg.fl_hip_pitch.params.position.min     = -12.5;
    msg.fl_hip_pitch.params.position.max     =  12.5;
    msg.fl_hip_pitch.params.velocity.min     = -65.0;
    msg.fl_hip_pitch.params.velocity.max     =  65.0;
    msg.fl_hip_pitch.params.kp.min           =  0.0;
    msg.fl_hip_pitch.params.kp.max           =  500.0;
    msg.fl_hip_pitch.params.kd.min           =  0.0;
    msg.fl_hip_pitch.params.kd.max           =  5.0;
    msg.fl_hip_pitch.params.i_ff.min         = -18.0;
    msg.fl_hip_pitch.params.i_ff.max         =  18.0;
    msg.fl_hip_pitch.ctrl_limits.position.min    = -3.14159;    // rad // -180 deg
    msg.fl_hip_pitch.ctrl_limits.position.max    =  3.14159;    // rad //  180 deg
    msg.fl_hip_pitch.ctrl_limits.velocity.min    = -1.0;        // rad/s 
    msg.fl_hip_pitch.ctrl_limits.velocity.max    =  1.0;        // rad/s 
    msg.fl_hip_pitch.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;       // A 
    msg.fl_hip_pitch.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;       // A 

    msg.fl_knee.params.can_id           =  6;
    msg.fl_knee.params.position.min     = -12.5;
    msg.fl_knee.params.position.max     =  12.5;
    msg.fl_knee.params.velocity.min     = -65.0;
    msg.fl_knee.params.velocity.max     =  65.0;
    msg.fl_knee.params.kp.min           =  0.0;
    msg.fl_knee.params.kp.max           =  500.0;
    msg.fl_knee.params.kd.min           =  0.0;
    msg.fl_knee.params.kd.max           =  5.0;
    msg.fl_knee.params.i_ff.min         = -18.0;
    msg.fl_knee.params.i_ff.max         =  18.0;
    msg.fl_knee.ctrl_limits.position.min    =  0.261799;    // rad // 15 deg
    msg.fl_knee.ctrl_limits.position.max    =  2.96706;     // rad // 170 deg
    msg.fl_knee.ctrl_limits.velocity.min    = -1.0;      // rad/s 
    msg.fl_knee.ctrl_limits.velocity.max    =  1.0;      // rad/s 
    msg.fl_knee.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;      // A 
    msg.fl_knee.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;      // A 

    /* RR Leg joint motors */
    msg.rr_hip_roll.params.can_id           =  7;
    msg.rr_hip_roll.params.position.min     = -12.5;
    msg.rr_hip_roll.params.position.max     =  12.5;
    msg.rr_hip_roll.params.velocity.min     = -65.0;
    msg.rr_hip_roll.params.velocity.max     =  65.0;
    msg.rr_hip_roll.params.kp.min           =  0.0;
    msg.rr_hip_roll.params.kp.max           =  500.0;
    msg.rr_hip_roll.params.kd.min           =  0.0;
    msg.rr_hip_roll.params.kd.max           =  5.0;
    msg.rr_hip_roll.params.i_ff.min         = -18.0;
    msg.rr_hip_roll.params.i_ff.max         =  18.0;
    msg.rr_hip_roll.ctrl_limits.position.min    = -1.5708; // rad // -90 deg
    msg.rr_hip_roll.ctrl_limits.position.max    =  1.5708; // rad //  90 deg
    msg.rr_hip_roll.ctrl_limits.velocity.min    = -1.0; // rad/s 
    msg.rr_hip_roll.ctrl_limits.velocity.max    =  1.0; // rad/s 
    msg.rr_hip_roll.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT; // A 
    msg.rr_hip_roll.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT; // A 

    msg.rr_hip_pitch.params.can_id           =  8;
    msg.rr_hip_pitch.params.position.min     = -12.5;
    msg.rr_hip_pitch.params.position.max     =  12.5;
    msg.rr_hip_pitch.params.velocity.min     = -65.0;
    msg.rr_hip_pitch.params.velocity.max     =  65.0;
    msg.rr_hip_pitch.params.kp.min           =  0.0;
    msg.rr_hip_pitch.params.kp.max           =  500.0;
    msg.rr_hip_pitch.params.kd.min           =  0.0;
    msg.rr_hip_pitch.params.kd.max           =  5.0;
    msg.rr_hip_pitch.params.i_ff.min         = -18.0;
    msg.rr_hip_pitch.params.i_ff.max         =  18.0;
    msg.rr_hip_pitch.ctrl_limits.position.min    = -3.14159;    // rad // -180 deg
    msg.rr_hip_pitch.ctrl_limits.position.max    =  3.14159;    // rad //  180 deg
    msg.rr_hip_pitch.ctrl_limits.velocity.min    = -1.0;        // rad/s 
    msg.rr_hip_pitch.ctrl_limits.velocity.max    =  1.0;        // rad/s 
    msg.rr_hip_pitch.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;       // A 
    msg.rr_hip_pitch.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;       // A 

    msg.rr_knee.params.can_id           =  9;
    msg.rr_knee.params.position.min     = -12.5;
    msg.rr_knee.params.position.max     =  12.5;
    msg.rr_knee.params.velocity.min     = -65.0;
    msg.rr_knee.params.velocity.max     =  65.0;
    msg.rr_knee.params.kp.min           =  0.0;
    msg.rr_knee.params.kp.max           =  500.0;
    msg.rr_knee.params.kd.min           =  0.0;
    msg.rr_knee.params.kd.max           =  5.0;
    msg.rr_knee.params.i_ff.min         = -18.0;
    msg.rr_knee.params.i_ff.max         =  18.0;
    msg.rr_knee.ctrl_limits.position.min    =  0.261799;    // rad // 15 deg
    msg.rr_knee.ctrl_limits.position.max    =  2.96706;     // rad // 170 deg
    msg.rr_knee.ctrl_limits.velocity.min    = -1.0;      // rad/s 
    msg.rr_knee.ctrl_limits.velocity.max    =  1.0;      // rad/s 
    msg.rr_knee.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;      // A 
    msg.rr_knee.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;      // A 

    /* RL Leg joint motors */
    msg.rl_hip_roll.params.can_id           =  10;
    msg.rl_hip_roll.params.position.min     = -12.5;
    msg.rl_hip_roll.params.position.max     =  12.5;
    msg.rl_hip_roll.params.velocity.min     = -65.0;
    msg.rl_hip_roll.params.velocity.max     =  65.0;
    msg.rl_hip_roll.params.kp.min           =  0.0;
    msg.rl_hip_roll.params.kp.max           =  500.0;
    msg.rl_hip_roll.params.kd.min           =  0.0;
    msg.rl_hip_roll.params.kd.max           =  5.0;
    msg.rl_hip_roll.params.i_ff.min         = -18.0;
    msg.rl_hip_roll.params.i_ff.max         =  18.0;
    msg.rl_hip_roll.ctrl_limits.position.min    = -1.5708; // rad // -90 deg
    msg.rl_hip_roll.ctrl_limits.position.max    =  1.5708; // rad //  90 deg
    msg.rl_hip_roll.ctrl_limits.velocity.min    = -1.0; // rad/s 
    msg.rl_hip_roll.ctrl_limits.velocity.max    =  1.0; // rad/s 
    msg.rl_hip_roll.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT; // A 
    msg.rl_hip_roll.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT; // A 

    msg.rl_hip_pitch.params.can_id           =  11;
    msg.rl_hip_pitch.params.position.min     = -12.5;
    msg.rl_hip_pitch.params.position.max     =  12.5;
    msg.rl_hip_pitch.params.velocity.min     = -65.0;
    msg.rl_hip_pitch.params.velocity.max     =  65.0;
    msg.rl_hip_pitch.params.kp.min           =  0.0;
    msg.rl_hip_pitch.params.kp.max           =  500.0;
    msg.rl_hip_pitch.params.kd.min           =  0.0;
    msg.rl_hip_pitch.params.kd.max           =  5.0;
    msg.rl_hip_pitch.params.i_ff.min         = -18.0;
    msg.rl_hip_pitch.params.i_ff.max         =  18.0;
    msg.rl_hip_pitch.ctrl_limits.position.min    = -3.14159;    // rad // -180 deg
    msg.rl_hip_pitch.ctrl_limits.position.max    =  3.14159;    // rad //  180 deg
    msg.rl_hip_pitch.ctrl_limits.velocity.min    = -1.0;        // rad/s 
    msg.rl_hip_pitch.ctrl_limits.velocity.max    =  1.0;        // rad/s 
    msg.rl_hip_pitch.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;       // A 
    msg.rl_hip_pitch.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;       // A 

    msg.rl_knee.params.can_id           =  12;
    msg.rl_knee.params.position.min     = -12.5;
    msg.rl_knee.params.position.max     =  12.5;
    msg.rl_knee.params.velocity.min     = -65.0;
    msg.rl_knee.params.velocity.max     =  65.0;
    msg.rl_knee.params.kp.min           =  0.0;
    msg.rl_knee.params.kp.max           =  500.0;
    msg.rl_knee.params.kd.min           =  0.0;
    msg.rl_knee.params.kd.max           =  5.0;
    msg.rl_knee.params.i_ff.min         = -18.0;
    msg.rl_knee.params.i_ff.max         =  18.0;
    msg.rl_knee.ctrl_limits.position.min    =  0.261799;    // rad // 15 deg
    msg.rl_knee.ctrl_limits.position.max    =  2.96706;     // rad // 170 deg
    msg.rl_knee.ctrl_limits.velocity.min    = -1.0;      // rad/s 
    msg.rl_knee.ctrl_limits.velocity.max    =  1.0;      // rad/s 
    msg.rl_knee.ctrl_limits.current.min     = -MAX_MOTOR_CURRENT;      // A 
    msg.rl_knee.ctrl_limits.current.max     =  MAX_MOTOR_CURRENT;      // A 

    return msg;
}