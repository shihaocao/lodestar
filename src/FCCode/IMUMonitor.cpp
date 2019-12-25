#include "IMUMonitor.hpp"

IMUMonitor::IMUMonitor(StateFieldRegistry &registry, 
    unsigned int offset, Adafruit_BNO055 &_imu)
    : TimedControlTask<void>(registry, "adcs_monitor", offset),
    imu(_imu),
    euler_angles("imu.euler_angles")
    {
        add_internal_field(euler_angles);
        //set up imu?
        if(!imu.begin()){
            //debug print
        }

        /* Use external crystal for better accuracy */
        imu.setExtCrystalUse(true);
    }

void IMUMonitor::execute(){

    //create internal container to dump data
    f_vector_t euler_angle_read;

    //create sensor event;
    sensors_event_t event;
    imu.getEvent(&event);
    


}