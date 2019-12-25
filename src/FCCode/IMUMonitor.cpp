#include "IMUMonitor.hpp"

IMUMonitor::IMUMonitor(StateFieldRegistry &registry, 
    unsigned int offset, Adafruit_BNO055 &_imu)
    : TimedControlTask<void>(registry, "imu_monitor", offset),
    imu(_imu),
    linear_acc_vec_f("imu.linear_acc_vec"),
    acc_vec_f("imu.acc_vec"),
    grav_vec_f("imu.grav_vec"),
    euler_vec_f("imu.euler_vec"),
    gyr_vec_f("imu.gyr_vec"),
    mag_vec_f("imu.mag_vec")
    {
        //add statefields to registry
        add_internal_field(linear_acc_vec_f);
        add_internal_field(acc_vec_f);
        add_internal_field(grav_vec_f);
        add_internal_field(euler_vec_f);
        add_internal_field(gyr_vec_f);
        add_internal_field(mag_vec_f);

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

    //linear_acc_vec is acceleration without gravity
    sensors_event_t linear_acc_vec,
        //acc_vec includes gravity
        acc_vec,
        //gravity vector
        grav_vec,
        //orientation in euler angles
        euler_vec,
        //gyroscope, angular acceleration vector
        gyr_vec,
        //magnetometer vector
        mag_vec;

    //poll actual i2c device, and fill containers
    imu.getEvent(&linear_acc_vec, Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu.getEvent(&acc_vec, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu.getEvent(&grav_vec, Adafruit_BNO055::VECTOR_GRAVITY);
    imu.getEvent(&euler_vec, Adafruit_BNO055::VECTOR_EULER);
    imu.getEvent(&gyr_vec, Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu.getEvent(&mag_vec, Adafruit_BNO055::VECTOR_MAGNETOMETER);

    //IF THIS IS TOO SLOW, DELETE READ OPERATIONS OF ^VECTORS WE DON'T NEED

    //dump temporary containers into statefields
    linear_acc_vec_f.set(linear_acc_vec);
    acc_vec_f.set(acc_vec);
    grav_vec_f.set(grav_vec);
    euler_vec_f.set(euler_vec);
    gyr_vec_f.set(gyr_vec);
    mag_vec_f.set(mag_vec);
}