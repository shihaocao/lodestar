#include "ServoControlTask.hpp"

ServoControlTask::ServoControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        servo_commands_f = find_internal_field<d_quat_t>("servo.cmd", __FILE__, __LINE__);
    }

void ServoControlTask::execute(){

    d_quat_t servo_commands = servo_commands_f->get();

    
}