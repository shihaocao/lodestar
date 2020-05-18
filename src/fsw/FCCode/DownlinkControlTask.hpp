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
    InternalStateField<unsigned int>* mm_fp;
    InternalStateField<f_vector_t>* linear_acc_fp;
    InternalStateField<f_vector_t>* euler_fp;
    InternalStateField<f_vector_t>* acc_fp;
    InternalStateField<f_vector_t>* gyr_fp;
    InternalStateField<d_quat_t>* quat_fp;

    // helper functions for debug out
    template<typename T, size_t N>
    void hardline_compact(std::array<T, N>& array){
        for(size_t i = 0; i < N-1; i++){
            hardline_element(array[i]);
            Serial.print(",");
        }
        hardline_element(array[N-1]);
        Serial.print(";");
    }

    template<typename T, size_t N>
    void airline_compact(std::array<T, N>& array){
        for(size_t i = 0; i < N - 1; i++){
            airline_element(array[i]);
            Serial1.print(",");
        }
        airline_element(array[N-1]);
        Serial1.print(";");
    }

    template<typename T>
    void hardline_element(T element){
        if(std::is_same<T, float>::value || std::is_same<T, double>::value)
            Serial.printf("%g", element);
        else if(std::is_same<T, unsigned char>::value || std::is_same<T, unsigned int>::value)
            Serial.printf("%u", element);
        else if(std::is_same<T, char>::value || std::is_same<T, int>::value)
            Serial.printf("%d", element);
        else
            Serial.print("[ERROR] UNEXPECTED ELEMENT TYPE.");
    }
    
    template<typename T>
    void airline_element(T element){
        if(std::is_same<T, float>::value || std::is_same<T, double>::value)
            Serial1.printf("%g", element);
        else if(std::is_same<T, unsigned char>::value || std::is_same<T, unsigned int>::value)
            Serial1.printf("%u", element);
        else if(std::is_same<T, char>::value || std::is_same<T, int>::value)
            Serial1.printf("%d", element);
        else
            Serial1.print("[ERROR] UNEXPECTED ELEMENT TYPE.");
    }

    template<typename T>
    void airline_solo(T element){
        airline_element(element);
        Serial1.print(";");
    }

    template<typename T>
    void hardline_solo(T element){
        hardline_element(element);
        Serial.print(";");
    }    
};

#endif
