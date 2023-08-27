uint8 id # 0 - 255

# Assign a leg joint to the motor
string leg # FR, FL, RR, RL
string joint # HIP_ROLL, HIP_PITCH, KNEE

# motor parameters
hyperdog_uros_msgs/MotorParams parameters

# motor control limits
hyperdog_uros_msgs/MotorCtrlLimits ctrl_limits