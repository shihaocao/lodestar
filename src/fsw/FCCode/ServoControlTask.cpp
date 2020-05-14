#include "ServoControlTask.hpp"

ServoControlTask::ServoControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        flap_commands_f = find_internal_field<f_quat_t>("gnc.flap_cmds", __FILE__, __LINE__);

        flap1.attach(SERVO::flap1_pin);
        flap2.attach(SERVO::flap2_pin);
        flap3.attach(SERVO::flap3_pin);
        flap4.attach(SERVO::flap4_pin);
    }

void ServoControlTask::execute(){

    f_quat_t flap_commands = flap_commands_f->get();
    f_quat_t unit_range;
    f_quat_t flap_servo_writes;

    // Serial.printf("GNC Commands: %f,%f,%f,%f\n",flap_commands[0],flap_commands[1],flap_commands[2],flap_commands[3]);

    for(unsigned int i = 0; i < SERVO::num_flaps; i++){
        unit_range[i] = (flap_commands[i] - SERVO::flap_cmd_min)/SERVO::servo_cmd_range;
    }
    for(unsigned int i = 0; i < SERVO::num_flaps; i++){
        flap_servo_writes[i] = (unit_range[i] * SERVO::servo_cmd_range) + SERVO::flap_write_min;
    }

    // for(unsigned int i = 0; i < SERVO::num_flaps; i++){
    //     flap_servo_writes[i] = 45;
    // }

    flap1.write(flap_servo_writes[0]);
    flap2.write(flap_servo_writes[1]);
    flap3.write(flap_servo_writes[2]);
    flap4.write(flap_servo_writes[3]);
}