#include "GNC.hpp"

GNC::GNC(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc", offset),
    flap_commands_fp("gnc.flap_cmds")
    {
        add_internal_field(flap_commands_fp);

        // default all flaps to no actuation
        flap_commands_fp.set(f_quat_t{
            0.0,
            0.0,
            0.0,
            0.0,
        });
    }

void GNC::execute(){

    f_quat_t flap_commands = flap_commands_fp.get();

    // the block below is dummy code that cycles the servos back and forth
    float speed = 0.5;
    if(flap_commands[0] > 90)
        inc_dir = -speed;
    if(flap_commands[0] <= 0)
        inc_dir = speed;
    for(unsigned int i = 0; i < SERVO::num_flaps; i++){
        flap_commands[i] += inc_dir;
    }

    flap_commands_fp.set(flap_commands);
    
    // flap_commands_fp.set(f_quat_t{
    //     20.0,
    //     30.0,
    //     40.0,
    //     50.0,
    // });

}