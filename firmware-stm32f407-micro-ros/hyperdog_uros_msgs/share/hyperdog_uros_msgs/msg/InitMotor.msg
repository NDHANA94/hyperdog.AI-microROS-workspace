uint8 id # 0 - 255

# Assign a leg joint to the motor
uint8 leg       # 0=FR,         1=FL,           2=RR,           3=RL
uint8 joint     # 0=HIP_ROLL,   1=HIP_PITCH,    2=KNEE

# motor parameters
hyperdog_uros_msgs/MotorParams parameters

# motor control limits
hyperdog_uros_msgs/MotorCtrlLimits ctrl_limitss