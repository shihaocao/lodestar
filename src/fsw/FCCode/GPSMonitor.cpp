#include "GPSMonitor.hpp"

GPSMonitor::GPSMonitor(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "imu_monitor", offset),
    //imu(_imu),
    functional_f("gps.functional"),
    has_fix_f("gps.fix"),

    linear_acc_vec_f("imu.linear_acc_vec"),
    acc_vec_f("imu.acc_vec"),
    net_acc_vec_f("imu.net_acc_vec"),
    grav_vec_f("imu.grav_vec"),
    euler_vec_f("imu.euler_vec"),
    gyr_vec_f("imu.gyr_vec"),
    mag_vec_f("imu.mag_vec"),
    quat_f("imu.quat"),
    quat_inv_f("imu.quat_inv")
    {
        //add statefields to registry
        add_internal_field(functional_f);
        add_internal_field(linear_acc_vec_f);
        add_internal_field(acc_vec_f);
        add_internal_field(net_acc_vec_f);
        add_internal_field(grav_vec_f);
        add_internal_field(euler_vec_f);
        add_internal_field(gyr_vec_f);
        add_internal_field(mag_vec_f);
        add_internal_field(quat_f);

    }

void GPSMonitor::execute(){

    //IF THIS IS TOO SLOW, DELETE READ OPERATIONS OF ^VECTORS WE DON'T NEED

    //IF BELOW TOO SLOW, STOP USING SENSOR EVENTS YIKES
    //dump temporary containers into statefields

    // lin::Vector3f v1{
    //     linear_acc_vec.acceleration.x, 
    //     linear_acc_vec.acceleration.y, 
    //     linear_acc_vec.acceleration.z};
    // linear_acc_vec_f.set({
    //     linear_acc_vec.acceleration.x, 
    //     linear_acc_vec.acceleration.y, 
    //     linear_acc_vec.acceleration.z});

    // OLD STD ARRAY VECTORS:

}