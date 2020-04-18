#include "GNC.hpp"

GNC::GNC(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc", offset),
    flap_commands_f("gnc.flap_cmds")
    {
        add_internal_field(flap_commands_f);
    }

void GNC::execute(){

    flap_commands_f.set(d_quat_t{
        20.0,
        30.0,
        40.0,
        50.0,
    });

}