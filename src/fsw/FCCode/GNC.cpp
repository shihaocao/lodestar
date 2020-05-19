#include "GNC.hpp"

GNC::GNC(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc", offset),
    flap_commands_f("gnc.flap_cmds")
    {
        add_internal_field(flap_commands_f);
        mission_mode_fp = find_internal_field<unsigned char>("ls.mode", __FILE__, __LINE__);

        // default all flaps to no actuation
        flap_commands_f.set(f_quat_t{
            0.0,
            0.0,
            0.0,
            0.0,
        });
    }

void GNC::execute(){

    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_fp->get());

    switch(mode) {
        case mission_mode_t::warmup:
            // dispatch_warmup();
            break;
        case mission_mode_t::initialization:
            // dispatch_initialization();
            break;
        case mission_mode_t::standby:
            dispatch_detumble(); //detumble to prep fins into right orientation
            break;
        case mission_mode_t::detumble:
            dispatch_detumble();
            break;
        case mission_mode_t::bellyflop:
            dispatch_bellyflop();
            break;
        case mission_mode_t::landed:
            // dispatch_landed();
            break;
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            // mission_mode_fp->set(static_cast<unsigned char>(mission_mode_t::landed));
            break;
    }

}

void GNC::dispatch_sweep(){
    f_quat_t flap_commands = flap_commands_f.get();

    // the block below is dummy code that cycles the servos back and forth
    float speed = 0.5;
    if(flap_commands[0] > 90)
        inc_dir = -speed;
    if(flap_commands[0] <= 0)
        inc_dir = speed;
    for(unsigned int i = 0; i < SERVO::num_flaps; i++){
        flap_commands[i] += inc_dir;
    }

    flap_commands_f.set(flap_commands);
}
void GNC::dispatch_detumble(){

    // everything 0 degrees of actuation
    flap_commands_f.set(f_quat_t{
        0.0,
        0.0,
        0.0,
        0.0
    });
}
void GNC::dispatch_bellyflop(){

    // 1. READ SENSORS
    // 2. RUN PID LOOP
    // 3. ???
    // 4. PROFIT???

    dispatch_sweep();

}