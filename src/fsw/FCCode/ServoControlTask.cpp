#include "ServoControlTask.hpp"

ServoControlTask::ServoControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        flap_commands_f = find_internal_field<d_quat_t>("gnc.flap_cmds", __FILE__, __LINE__);

        flap1.attach(SERVO::flap1_pin);
        flap2.attach(SERVO::flap2_pin);
        flap3.attach(SERVO::flap3_pin);
        flap4.attach(SERVO::flap4_pin);
    }

void ServoControlTask::execute(){

    d_quat_t flap_commands = flap_commands_f->get();

    
    Serial1.write("TEST-HI-GOVIND\n");

    for(int i = 0; i < 4; i++)
}