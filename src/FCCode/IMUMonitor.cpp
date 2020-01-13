#include "IMUMonitor.hpp"

IMUMonitor::IMUMonitor(StateFieldRegistry &registry, 
    unsigned int offset, Adafruit_BNO055 &_imu)
    : TimedControlTask<void>(registry, "imu_monitor", offset),
    imu(_imu),
    functional_f("imu.functional"),
    linear_acc_vec_f("imu.linear_acc_vec"),
    acc_vec_f("imu.acc_vec"),
    grav_vec_f("imu.grav_vec"),
    euler_vec_f("imu.euler_vec"),
    gyr_vec_f("imu.gyr_vec"),
    mag_vec_f("imu.mag_vec")
    {
        //add statefields to registry
        add_internal_field(functional_f);
        add_internal_field(linear_acc_vec_f);
        add_internal_field(acc_vec_f);
        add_internal_field(grav_vec_f);
        add_internal_field(euler_vec_f);
        add_internal_field(gyr_vec_f);
        add_internal_field(mag_vec_f);

        //set up imu?
        if(!imu.begin()){
            //debug print
            functional_f.set(false);
        }
        else
        {
            functional_f.set(true);
        }

        /* Use external crystal for better accuracy */
        imu.setExtCrystalUse(true);
    }

void IMUMonitor::execute(){

    //linear_acc_vec is acceleration without gravity
    //sensors_event_t linear_acc,
        //acc_vec includes gravity
        //acc,
        //gravity vector
        //grav,
        //orientation in euler angles
        //euler;
        // //gyroscope, angular acceleration vector
        // gyr,
        // //magnetometer vector
        // mag;

    // int8_t boardTemp = imu.getTemp();
    // Serial.print(F("temperature: "));
    // Serial.println(boardTemp);

    //poll actual i2c device, and fill containers
    // imu.getEvent(&linear_acc, Adafruit_BNO055::VECTOR_LINEARACCEL);
    // // imu.getEvent(&acc, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    // imu.getEvent(&grav, Adafruit_BNO055::VECTOR_GRAVITY);
    //imu.getEvent(&euler, Adafruit_BNO055::VECTOR_EULER);
    //delay(100);
    // imu.getEvent(&gyr, Adafruit_BNO055::VECTOR_GYROSCOPE);
    // imu.getEvent(&mag, Adafruit_BNO055::VECTOR_MAGNETOMETER);

    //IF THIS IS TOO SLOW, DELETE READ OPERATIONS OF ^VECTORS WE DON'T NEED

    //IF BELOW TOO SLOW, STOP USING SENSOR EVENTS YIKES
    //dump temporary containers into statefields
    delay(100);
    //f_vector_t linear_acc_vec;
    sensors_event_t linear_acc;
    imu.getEvent(&linear_acc, Adafruit_BNO055::VECTOR_LINEARACCEL);

    linear_acc_vec_f.set(f_vector_t{{
        linear_acc.acceleration.x, 
        linear_acc.acceleration.y, 
        linear_acc.acceleration.z}});

    acc_vec_f.set(f_vector_t({
        9.0f, 
        2.0f, 
        1.0f}));

    // acc_vec_f.set(f_vector_t{
    //     acc_vec.acceleration.x, 
    //     acc_vec.acceleration.y, 
    //     acc_vec.acceleration.z
    // });

    f_vector_t grav_vec;
    sensors_event_t grav;
    imu.getEvent(&grav, Adafruit_BNO055::VECTOR_GRAVITY);
    grav_vec[0] = grav.acceleration.x;
    grav_vec[1] = grav.acceleration.y;
    grav_vec[2] = grav.acceleration.z;
    grav_vec_f.set(grav_vec);

    sensors_event_t euler;
    imu.getEvent(&euler, Adafruit_BNO055::VECTOR_EULER);
    euler_vec_f.set(f_vector_t{
        euler.orientation.x,
        euler.orientation.y,
        euler.orientation.z,
    });
    
    // gyr_vec_f.set(f_vector_t{
    //     gyr_vec.gyro.x,
    //     gyr_vec.gyro.y,
    //     gyr_vec.gyro.z,
    // });

    // mag_vec_f.set(f_vector_t{
    //     mag_vec.magnetic.x,
    //     mag_vec.magnetic.y,
    //     mag_vec.magnetic.z
    // });
}