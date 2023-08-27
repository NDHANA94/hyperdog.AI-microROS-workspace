# leg and joint of the motor
string leg # FR, FL, RR, RL
string joint # HIP_ROLL, HIP_PITCH, KNEE

# special commands
bool enable
bool disable
bool set_zero

# control commands
float64 desire_position
float64 desire_velocity
float64 kp
float64 kd
float64 i_ff