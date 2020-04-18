#ifndef GNC_HPP_
#define GNC_HPP_
#pragma once

#include "TimedControlTask.hpp"

/**
* @brief Gets inputs from the ADCS box and dumps them into the state
* fields listed below.
*/
class GNC : public TimedControlTask<void>
{
public:
    /**
     * @brief Construct a new ADCSBoxMonitor control task
     * 
     * @param registry input StateField registry
     * @param offset control task offset
     */
    GNC(StateFieldRegistry &registry, unsigned int offset);

    /**
    * @brief Gets inputs from the ADCS box and dumps them into the state
    * fields listed below.
    */
    void execute() override;

protected:
    /**
    * @brief Inputs to get from GNC.
    */

    InternalStateField<f_quat_t> flap_commands_f;

    // eventually not needed, just was for debug
    int inc_dir = 0;
};

#endif
