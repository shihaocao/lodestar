#include "MissionManager.hpp"

MissionManager::MissionManager(StateFieldRegistry& registry, unsigned int offset) :
    TimedControlTask<void>(registry, "mission_ct", offset),
    mission_mode_f("ls.mode"),
    ground_level_f("ls.ground_level")
{
    add_internal_field(mission_mode_f);
    add_internal_field(ground_level_f);

    alt_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);

    // adcs_mode_fp = find_writable_field<unsigned char>("adcs.mode", __FILE__, __LINE__);
    // adcs_cmd_attitude_fp = find_writable_field<f_quat_t>("adcs.cmd_attitude", __FILE__, __LINE__);
    // adcs_ang_rate_fp = find_readable_field<float>("adcs.ang_rate", __FILE__, __LINE__);
    // adcs_min_stable_ang_rate_fp = find_writable_field<float>("adcs.min_stable_ang_rate", __FILE__, __LINE__);
    // radio_mode_fp = find_readable_field<unsigned char>("radio.mode", __FILE__, __LINE__);

    mission_mode_f.set(static_cast<unsigned int>(mission_mode_t::warmup));
    ground_level_f.set(0);

    enter_init_ccno = -1;
}

void MissionManager::execute() {
    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_f.get());
    switch(mode) {
        case mission_mode_t::warmup:
            dispatch_warmup();
            break;
        case mission_mode_t::initialization:
            dispatch_initialization();
            break;
        case mission_mode_t::standby:
            dispatch_standby();
            break;
        case mission_mode_t::detumble:
            dispatch_detumble();
            break;
        case mission_mode_t::bellyflop:
            dispatch_bellyflop();
            break;
        case mission_mode_t::landed:
            dispatch_landed();
            break;
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            mission_mode_f.set(static_cast<unsigned int>(mission_mode_t::landed));
            break;
    }
}

void MissionManager::set_mission_mode(mission_mode_t mode){
    mission_mode_f.set(static_cast<unsigned int>(mode));
}

void MissionManager::dispatch_warmup() {
    // if 5 sec elapse go to init
    if(millis() > MM::warmup_millis){
        set_mission_mode(mission_mode_t::initialization);
        enter_init_ccno = control_cycle_count;
    }
}

void MissionManager::dispatch_initialization() {
    // weight the current altitude readings
    ground_level_f.set(ground_level_f.get() + alt_fp->get() / MM::init_cycles);

    if(control_cycle_count - enter_init_ccno >= MM::init_cycles){
        set_mission_mode(mission_mode_t::standby);
    }
}

void MissionManager::dispatch_standby() {
    
}

//lode star needs detumble too. If we're tumbling waaaay to fast, step one should just be to keep fins out to zero out all spin
void MissionManager::dispatch_detumble() {

}

void MissionManager::dispatch_bellyflop() {
    //actuate as you would during belly flop
}

void MissionManager::dispatch_landed() {
    //dump data from registry to SD Card
}

