#include "DownlinkControlTask.hpp"

DownlinkControlTask::DownlinkControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        altitude_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);
        

        #ifdef SERIAL_DEBUG
        Serial.begin(9600);
        #endif
    }

void DownlinkControlTask::execute(){

    #ifdef SERIAL_DEBUG
    Serial.printf("Altitude (m): %f\n", altitude_fp->get());
    #endif
}