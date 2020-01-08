#include "DownlinkControlTask.hpp"

DownlinkControlTask::DownlinkControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        altitude_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);

        Serial.begin(9600);
    }

void DownlinkControlTask::execute(){
    
    Serial.printf("Altitude (m): %f\n", altitude_fp->get());
}