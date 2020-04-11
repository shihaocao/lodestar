#include "GNC.hpp"

GNC::GNC(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc", offset)
    {
        servo_commands_f = find_internal_field<d_quat_t>("servo.cmd", __FILE__, __LINE__);
    }

void GNC::execute(){

    d_quat_t servo_commands = servo_commands_f->get();

    
}