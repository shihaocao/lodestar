#include "GNC.hpp"

GNC::GNC(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc", offset),
    servo_commands_f("gnc.servo_cmds")
    {

    }

void GNC::execute(){

    servo_commands_f.set(d_quat_t{
        20.0,
        30.0,
        40.0,
        50.0,
    });

}