#include "BMPMonitor.hpp"

BMPMonitor::BMPMonitor(StateFieldRegistry &registry, 
    unsigned int offset, Adafruit_BMP280 &_bmp)
    : TimedControlTask<void>(registry, "bmp_monitor", offset),
    bmp(_bmp),
    temp_f("bmp.temp"),
    pressure_f("bmp.pressure")
    {
        //add statefields to registry
        add_internal_field(temp_f);
        add_internal_field(pressure_f);

        //set up imu?
        if(!bmp.begin()){
            //debug print
            //TODO THROW ERROR?
        }

        /* Default settings from datasheet. */
        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    }

void BMPMonitor::execute(){

    //linear_acc_vec is acceleration without gravity
    sensors_event_t
        // temperature
        temp,
        // pressure
        pressure;

    // poll sensor pointers
    bmp_temp->getEvent(&temp);
    bmp_pressure->getEvent(&pressure);

    //dump temporary containers into statefields
    temp_f.set(temp);
    pressure_f.set(pressure);
}