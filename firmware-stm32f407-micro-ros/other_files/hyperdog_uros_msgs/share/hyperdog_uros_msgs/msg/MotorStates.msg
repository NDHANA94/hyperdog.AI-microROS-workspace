# std_msgs/Header header

# motor details
string leg # FR, FL, RR, RL
string joint # HIP_ROLL, HIP_PITCH, KNEE

# states
bool is_available
bool is_enabled
bool is_error
int16 error_code
string status_msg

# motor feedback data
hyperdog_uros_msgs/MotorFeedback feedback