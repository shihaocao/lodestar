#ifndef DOWNLINK_CONTROL_TASK_HPP_
#define DOWNLINK_CONTROL_TASK_HPP_
#pragma once

#include "TimedControlTask.hpp"

/**
* @brief Gets inputs from the ADCS box and dumps them into the state
* fields listed below.
*/
class DownlinkControlTask : public TimedControlTask<void>
{
public:
    /**
     * @brief Construct a new ADCSBoxMonitor control task
     * 
     * @param registry input StateField registry
     * @param offset control task offset
     */
    DownlinkControlTask(StateFieldRegistry &registry, unsigned int offset);

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

    InternalStateField<float>* altitude_fp;
    InternalStateField<f_vector_t>* linear_acc_fp;
    InternalStateField<f_vector_t>* euler_fp;
    InternalStateField<f_vector_t>* acc_fp;
    InternalStateField<f_vector_t>* gyr_fp;
};

#endif
