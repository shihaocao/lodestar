#include "GNC.hpp"

GNC::GNC(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc", offset),
    flap_commands_f("gnc.flap_cmds")
    {
        add_internal_field(flap_commands_f);

        // default all flaps to no actuation
        flap_commands_f.set(f_quat_t{
            0.0,
            0.0,
            0.0,
            0.0,
        });
    }

void GNC::execute(){

    f_quat_t flap_commands = flap_commands_f.get();

    int inc_dir = 1;
    if(flap_commands[0] == 90)
        inc_dir = -1;
    else if(flap_commands[0] == 0)
        inc_dir = 1;

    for(unsigned int i = 0; i < SERVO::num_flaps; i++){
        flap_commands[i] += inc_dir;
    }

    flap_commands_f.set(flap_commands);
    // flap_commands_f.set(f_quat_t{
    //     20.0,
    //     30.0,
    //     40.0,
    //     50.0,
    // });

}