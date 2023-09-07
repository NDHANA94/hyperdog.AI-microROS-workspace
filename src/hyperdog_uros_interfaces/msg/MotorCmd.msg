# leg and joint of the motor
uint8 leg       # 0=FR,       1=FL,        2=RR,    3=RL
uint8 joint     # 0=HIP_ROLL, 1=HIP_PITCH, 2=KNEE

# special commands
bool enable
bool disable
bool set_zero

# control commands
float32 desire_position
float32 desire_velocity
float32 kp
float32 kd
float32 i_ff