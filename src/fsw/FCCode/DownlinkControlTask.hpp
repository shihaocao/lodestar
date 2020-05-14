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
    InternalStateField<d_quat_t>* quat_fp;

    // helper functions for debug out
    template<typename T, size_t N>
    void hardline_compact(std::array<T, N>& array){
        for(size_t i = 0; i < N; i++){
            hardline_element(array[i]);
        }
    }

    template<typename T, size_t N>
    void airline_compact(std::array<T, N>& array){
        for(size_t i = 0; i < N; i++){
            airline_element(array[i]);
        }
    }

    template<typename T>
    void hardline_element(T element){
        if(std::is_same<T, float>::value || std::is_same<T, double>::value)
            Serial.printf("%f,", element);
        else if(std::is_same<T, unsigned char>::value || std::is_same<T, unsigned int>::value)
            Serial.printf("%u,", element);
        else if(std::is_same<T, char>::value || std::is_same<T, int>::value)
            Serial.printf("%d,", element);
        else
            Serial.print("[ERROR] UNEXPECTED ELEMENT TYPE.");
    }

    template<typename T>
    void airline_element(T element){
        if(std::is_same<T, float>::value || std::is_same<T, double>::value)
            Serial1.printf("%f,", element);
        else if(std::is_same<T, unsigned char>::value || std::is_same<T, unsigned int>::value)
            Serial1.printf("%u,", element);
        else if(std::is_same<T, char>::value || std::is_same<T, int>::value)
            Serial1.printf("%d,", element);
        else
            Serial1.print("[ERROR] UNEXPECTED ELEMENT TYPE.");
    }
};

#endif
