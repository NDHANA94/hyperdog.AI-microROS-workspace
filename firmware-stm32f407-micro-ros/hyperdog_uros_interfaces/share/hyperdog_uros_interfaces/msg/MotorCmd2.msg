# Id of the motor
uint8 can_id

# Special commands
bool enable
bool disable
bool set_zero

# control commands
float64 desire_position
float64 desire_velocity
float64 kp
float64 kd
float64 i_ff