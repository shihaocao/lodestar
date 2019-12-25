#ifndef IMU_MONITOR_HPP_
#define IMU_MONITOR_HPP_
#pragma once

#include "TimedControlTask.hpp"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
//#include <utility/imumaths.h>

/**
* @brief Gets inputs from the ADCS box and dumps them into the state
* fields listed below.
*/
class IMUMonitor : public TimedControlTask<void>
{
public:
    /**
     * @brief Construct a new ADCSBoxMonitor control task
     * 
     * @param registry input StateField registry
     * @param offset control task offset
     * @param _imu the input adcs system
     */
    IMUMonitor(StateFieldRegistry &registry, unsigned int offset, Adafruit_BNO055& _imu);

    /** ADCS Driver. **/
    //Devices::ADCS& adcs_system;
    Adafruit_BNO055& imu;

    /**
    * @brief Gets inputs from the ADCS box and dumps them into the state
    * fields listed below.
    */
    void execute() override;

protected:
    /**
    * @brief Inputs to get from ADCS box.
    */

    //! IMU Read Statefields, Internal float for now
    //InternalStateField<f_vector_t> euler_angles;

    //imu sensor event
    //InternalStateField<sensors_event_t> imu_sensor_event;

    InternalStateField<sensors_event_t> linear_acc_vec_f,
        //acc_vec includes gravity
        acc_vec_f,
        //gravity vector
        grav_vec_f,
        //orientation in euler angles
        euler_vec_f,
        //gyroscope, angular acceleration vector
        gyr_vec_f,
        //magnetometer vector
        mag_vec_f;
 
};

#endif
