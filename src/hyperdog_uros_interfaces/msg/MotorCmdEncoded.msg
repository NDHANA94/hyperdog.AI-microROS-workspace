# Id of the motor
uint8 can_id

# Special commands
bool enable
bool disable
bool set_zero

# encoded control commands to reduce memory consumption
uint8[8] cmd