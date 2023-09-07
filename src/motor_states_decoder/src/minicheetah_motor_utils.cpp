
#include "motor_states_decoder/minicheetah_motor_utils.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "hyperdog_ctrl_legs/initLegMotorsMsg_config.hpp" 
#include "hyperdog_uros_interfaces/msg/init_leg_motors.hpp"
#include "hyperdog_uros_interfaces/msg/motor_feedback_encoded.hpp"

#include <array>

// std::string ctrlLegs_pkgName = "hyperdog_ctrl_legs";
// std::string ctrlLegs_path = ament_index_cpp::get_package_share_directory("hyperdog_ctrl_legs");

std::string motor_name_[12] = {"fr_hip_roll", "fr_hip_pitch", "fr_knee", 
                               "fl_hip_roll", "fl_hip_pitch", "fl_knee",
                               "rr_hip_roll", "rr_hip_pitch", "rr_knee",
                               "rl_hip_roll", "rl_hip_pitch", "rl_knee"};




float _fminf(float x, float y)
{
    return (((x) < (y)) ? (x) : (y));
}

float _fmaxf(float x, float y)
{
    return (((x) > (y)) ? (x) : (y));
}

int _float2uint(float x, float x_min, float x_max, int bits)
{
    float span = x_max - x_min;
    float offset = x_min;
    return (int) ((x - offset) * ((float)((1<<bits)-1))/span);
}

float _uint2float(int x_int, float x_min, float x_max, int bits)
{
    float span = x_max - x_min;
    float offset = x_min;
    return ((float)x_int)*span/((float)((1<<bits)-1)) + offset;
}


auto m_params = get_initLegMotors_reqMsg();

hyperdog_uros_interfaces::msg::MotorFeedback
get_decoded(std::array<uint8_t, 6U> data, hyperdog_uros_interfaces::msg::MotorParams params)
{
    auto fb_dec = hyperdog_uros_interfaces::msg::MotorFeedback();

    int p_int   = (data[1] << 8) | (data[2]);
    int v_int   = (data[3] << 4) | (data[4] >> 4);
    int t_int  = ((data[4]&0xF) << 8) | (data[5]);


    fb_dec.can_id = data[0];
    fb_dec.position = _uint2float(
        p_int, 
        params.position.min,
        params.position.max,
        16);
    fb_dec.velocity = _uint2float(
        v_int, 
        params.velocity.min,
        params.velocity.max,
        12);
    fb_dec.torque = _uint2float(
        t_int, 
        -40,
        40,
        12);

    return fb_dec;
}


hyperdog_uros_interfaces::msg::MotorFeedback
unpack_motor_feedback(hyperdog_uros_interfaces::msg::MotorFeedbackEncoded fb_enc)
{
    
    auto fb_dec = hyperdog_uros_interfaces::msg::MotorFeedback();
    
    if(m_params.fr_hip_roll.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.fr_hip_roll.params);
    else if(m_params.fr_hip_pitch.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.fr_hip_pitch.params);
    else if(m_params.fr_knee.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.fr_knee.params);

    else if(m_params.fl_hip_roll.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.fl_hip_roll.params);
    else if(m_params.fl_hip_pitch.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.fl_hip_pitch.params);
    else if(m_params.fl_knee.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.fl_knee.params);

    else if(m_params.rr_hip_roll.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.rr_hip_roll.params);
    else if(m_params.rr_hip_pitch.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.rr_hip_pitch.params);
    else if(m_params.rr_knee.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.rr_knee.params);
    else if(m_params.rl_hip_roll.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.rl_hip_roll.params);
    else if(m_params.rl_hip_pitch.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.rl_hip_pitch.params);
    else if(m_params.rl_knee.params.can_id == fb_enc.data[0])
        fb_dec = get_decoded(fb_enc.data, m_params.rl_knee.params);

    return fb_dec;
}



