#include "GNC_a.hpp"

GNC_a::GNC_a(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc_a", offset),
    fin_commands_f("gnc_a.fin_cmds")
    {
        add_internal_field(fin_commands_f);
        mission_mode_fp = find_internal_field<unsigned char>("ls.mode", __FILE__, __LINE__);
        omega_vec_fp = find_internal_field<lin::Vector3f>("imu.gyr_vec", __FILE__, __LINE__);
        acc_vec_fp = find_internal_field<lin::Vector3f>("imu.acc_vec", __FILE__, __LINE__);
        euler_vec_fp = find_internal_field<lin::Vector3f>("imu.euler_vec", __FILE__, __LINE__);
        quat_fp = find_internal_field<lin::Vector4d>("imu.quat", __FILE__, __LINE__);

        // default all fins to no actuation
        fin_commands_f.set({
            0.0,
            0.0,
            0.0,
            0.0,
        });
    }

void GNC_a::execute(){

    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_fp->get());

    switch(mode) {
        case mission_mode_t::starhopper:
             tvc();
            break;
        
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            // mission_mode_fp->set(static_cast<unsigned char>(mission_mode_t::landed));
            break;
    }

}

void GNC_a::tvc(){
    lin::Vector4f fin_commands = fin_commands_f.get();

    //Sets all fins to 30 degrees as a test
    fin_commands(0)=30;
    fin_commands(1)=30;
    fin_commands(2)=30;
    fin_commands(3)=30;
    fin_commands_f.set(fin_commands);
}

