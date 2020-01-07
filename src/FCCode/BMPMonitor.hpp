#ifndef BMP_MONITOR_HPP_
#define BMP_MONITOR_HPP_
#pragma once

#include "TimedControlTask.hpp"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

/**
* @brief Gets inputs from the BMP280 and dumps them into the state
* fields listed below.
*/
class BMPMonitor : public TimedControlTask<void>
{
public:
    /**
     * @brief Construct a new ADCSBoxMonitor control task
     * 
     * @param registry input StateField registry
     * @param offset control task offset
     * @param _bmp the BMP280 driver object reference
     */
    BMPMonitor(StateFieldRegistry &registry, unsigned int offset, Adafruit_BMP280& _bmp);

    /** BMP280 device */
    Adafruit_BMP280 bmp;

    /**
    * @brief Gets inputs from the BMP280 and dumps them into the state
    * fields listed below.
    */
    void execute() override;

protected:

    /**
    * @brief Inputs to get from BMP280
    */
    InternalStateField<sensors_event_t>
        // temperature state field
        temp_f, 
        // pressure state field
        pressure_f;
 
};

#endif
