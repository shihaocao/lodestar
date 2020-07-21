#ifndef SD_CARD_CONTROL_TASK_HPP_
#define SD_CARD_CONTROL_TASK_HPP_
#pragma once
#include <Servo.h>

#include "TimedControlTask.hpp"

/**
* @brief Gets inputs from the ADCS box and dumps them into the state
* fields listed below.
*/
class SDCardControlTask : public TimedControlTask<void>
{
public:
    /**
     * @brief Construct a new ADCSBoxMonitor control task
     * 
     * @param registry input StateField registry
     * @param offset control task offset
     */
    SDCardControlTask(StateFieldRegistry &registry, unsigned int offset);

    /**
    * @brief Gets inputs from the ADCS box and dumps them into the state
    * fields listed below.
    */
    void execute() override;

protected:
    /**
    * @brief Inputs to get from GNC.
    */
    InternalStateField<lin::Vector4f>* flap_commands_fp;
    InternalStateField<bool>* servo_on_fp;
    InternalStateField<lin::Vector4f>* fin_commands_fp;

    void actuate();
};

#endif
