#include "DownlinkControlTask.hpp"

DownlinkControlTask::DownlinkControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        pinMode(13, OUTPUT);
    }

void DownlinkControlTask::execute(){
    if(control_cycle_count % 2 == 0)
        digitalWrite(13, HIGH);
    else
        digitalWrite(13, LOW);
}