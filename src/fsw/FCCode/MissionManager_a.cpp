#include "MissionManager_a.hpp"

MissionManager_a::MissionManager_a(StateFieldRegistry& registry, unsigned int offset) :
    TimedControlTask<void>(registry, "mission_ct", offset),
    mission_mode_f("ls.mode"),
    acc_error_f("ls.acc_error"),
    init_quat_d("ls.init_quat"),
    ground_level_f("ls.ground_level"),
    engine_on_f("ls.engine_on"),
    servo_on_f("ls.servo_on"),
    agl_alt_f("ls.agl")
{
    add_internal_field(mission_mode_f);
    add_internal_field(acc_error_f);
    add_internal_field(init_quat_d);
    add_internal_field(ground_level_f);
    add_internal_field(engine_on_f);
    add_internal_field(servo_on_f);
    add_internal_field(agl_alt_f);

    alt_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);
    acc_vec_fp = find_internal_field<lin::Vector3f>("imu.acc_vec", __FILE__, __LINE__);
    quat_fp = find_internal_field<lin::Vector4d>("imu.quat", __FILE__, __LINE__);
    lin_acc_vec_fp = find_internal_field<lin::Vector3f>("imu.linear_acc_vec", __FILE__, __LINE__);
    omega_vec_fp = find_internal_field<lin::Vector3f>("imu.gyr_vec", __FILE__, __LINE__);

    sys_cal = find_internal_field<unsigned char>("imu.sys_cal", __FILE__, __LINE__);
    gyro_cal = find_internal_field<unsigned char>("imu.gyro_cal", __FILE__, __LINE__);
    accel_cal = find_internal_field<unsigned char>("imu.accel_cal", __FILE__, __LINE__);
    mag_cal = find_internal_field<unsigned char>("imu.mag_cal", __FILE__, __LINE__);
    
    // adcs_mode_fp = find_writable_field<unsigned char>("adcs.mode", __FILE__, __LINE__);
    // adcs_cmd_attitude_fp = find_writable_field<f_quat_t>("adcs.cmd_attitude", __FILE__, __LINE__);
    // adcs_ang_rate_fp = find_readable_field<float>("adcs.ang_rate", __FILE__, __LINE__);
    // adcs_min_stable_ang_rate_fp = find_writable_field<float>("adcs.min_stable_ang_rate", __FILE__, __LINE__);
    // radio_mode_fp = find_readable_field<unsigned char>("radio.mode", __FILE__, __LINE__);

    mission_mode_f.set(static_cast<unsigned char>(mission_mode_t::warmup));
    ground_level_f.set(0);

    enter_init_ccno = -1;
    enter_freefall_cnno = -1;

    servo_on_f.set(false);
    engine_on_f.set(false);
}

void MissionManager_a::execute() {
    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_f.get());

    calibrate_data();

    if(millis() > MM::FTS_millis){
        Serial.print("Terminated"); ///////////////////////////////////
        set_mission_mode(mission_mode_t::landed);
    }
    switch(mode) {
        case mission_mode_t::warmup:
            Serial.println("Warmup"); ///////////////////////////////////
            dispatch_warmup();
            break;
        case mission_mode_t::pause:
            Serial.println("Pause"); ///////////////////////////////////
            pause();
            break;
        case mission_mode_t::initialization:
            Serial.println("Initialization      "); ///////////////////////////////////
            dispatch_initialization();
            break;
        case mission_mode_t::starhopper1:
            tvc();
            break;
        case mission_mode_t::starhopper2:
            tvc();
            break;
        case mission_mode_t::starhopper3:
            tvc();
            break;
        case mission_mode_t::landed:
            Serial.print("Landed"); ///////////////////////////////////
            dispatch_landed();
            break;
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            mission_mode_f.set(static_cast<unsigned char>(mission_mode_t::landed));
            break;
    }
}

void MissionManager_a::set_mission_mode(mission_mode_t mode){
    mission_mode_f.set(static_cast<unsigned char>(mode));
}
void MissionManager_a::calibrate_data(){

    agl_alt_f.set(alt_fp->get() - ground_level_f.get());
    

}
void MissionManager_a::dispatch_warmup() {

    unsigned char calibration_sum = sys_cal->get() + accel_cal->get() + gyro_cal->get() + mag_cal->get();

    // if 5 sec elapse go to init
    // AND ALSO CHECK THAT ALL SENSORS HAVE HIT 3,3,3,3 calibration
    #ifdef WARMUP_CALI
    if(millis() > MM::warmup_millis && calibration_sum == 12){
    #else
    

    if(accel_cal->get()==3){ //&&m millis() > MM::warmup_millis){
    #endif
        pause_ccno = control_cycle_count;
        set_mission_mode(mission_mode_t::pause);
    }
    calibration_sum += 1; // to avoid "unused error", ignore this line
}


void MissionManager_a::pause() {
    if(control_cycle_count-pause_ccno>=30){
        enter_init_ccno = control_cycle_count;
        set_mission_mode(mission_mode_t::initialization);
    }
}

void MissionManager_a::dispatch_initialization() {

    // weight the current altitude readings
    ground_level_f.set(ground_level_f.get() + alt_fp->get() / MM::init_cycles);

    init_quat_d.set( init_quat_d.get() + quat_fp->get() / MM::init_cycles);

    acc_error_f.set( acc_error_f.get() + lin_acc_vec_fp->get() / MM::init_cycles);

    Serial.print("      (");
    Serial.print(acc_error_f.get()(0));
    Serial.print(",");
    Serial.print(acc_error_f.get()(1));
    Serial.print(",");
    Serial.print(acc_error_f.get()(2));
    Serial.print(")");


    double quat_norm=lin::norm(init_quat_d.get());

    init_quat_d.set({
        init_quat_d.get()(0)/quat_norm,
        init_quat_d.get()(1)/quat_norm,
        init_quat_d.get()(2)/quat_norm,
        init_quat_d.get()(3)/quat_norm,
    });

    if(control_cycle_count - enter_init_ccno >= MM::init_cycles){
        set_mission_mode(mission_mode_t::starhopper1);
        servo_on_f.set(true);
        engine_on_f.set(true);
    }
}


void MissionManager_a::tvc() {
    //Exit condition for starhopper is if the FTS time is exceeded (Eventaully it will be an altitude condition)
    if(millis() > MM::FTS_millis){
        set_mission_mode(mission_mode_t::landed);
    }
}


void MissionManager_a::dispatch_landed() {
    //dump data from registry to SD Card
    // safe vehicle

    servo_on_f.set(false);
    engine_on_f.set(false);
}

