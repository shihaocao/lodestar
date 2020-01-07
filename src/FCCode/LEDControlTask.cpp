#include "LEDControlTask.hpp"

LEDControlTask::LEDControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "led_control_task", offset)
    {
        pinMode(13, OUTPUT);
    }

void LEDControlTask::execute(){
    if(control_cycle_count % 2 == 0)
        digitalWrite(13, HIGH);
    else
        digitalWrite(13, LOW);
}