#ifndef GNC_a_HPP_
#define GNC_a_HPP_
#pragma once

#include <math.h>
#include "TimedControlTask.hpp"
#include "mission_mode_t.enum"
/**
* @brief Gets inputs from the ADCS box and dumps them into the state
* fields listed below.
*/
class GNC_a : public TimedControlTask<void>
{
public:
    /**
     * @brief Construct a new ADCSBoxMonitor control task
     * 
     * @param registry input StateField registry
     * @param offset control task offset
     */
    GNC_a(StateFieldRegistry &registry, unsigned int offset);

    /**
    * @brief Gets inputs from the ADCS box and dumps them into the state
    * fields listed below.
    */
    void execute() override;

protected:

    InternalStateField<unsigned char>* mission_mode_fp;
    InternalStateField<lin::Vector3f>* omega_vec_fp;
    InternalStateField<lin::Vector3f>* acc_vec_fp;
    InternalStateField<lin::Vector3f>* lin_acc_vec_fp;
    InternalStateField<lin::Vector3f>* acc_error_fp;
    InternalStateField<lin::Vector3f>* euler_vec_fp;
    InternalStateField<lin::Vector3f>* grav_vec_fp;
    InternalStateField<lin::Vector4d>* quat_fp;
    InternalStateField<lin::Vector4d>* init_quat_dp;
    InternalStateField<lin::Vector4d>* quat_inv_fp;


    /**
    * @brief Outputs of GNC_a
    */
    InternalStateField<lin::Vector4f> fin_commands_f;
    InternalStateField<lin::Vector3f> glob_acc_vec_f;
    InternalStateField<lin::Vector2f> thrust_commands_f;
    InternalStateField<lin::Vector3d> setpoint_d;
    InternalStateField<lin::Vector3d> velocity_d;
    InternalStateField<lin::Vector3d> position_d;
    InternalStateField<lin::Vector3d> glob_pos_err_d;
    InternalStateField<lin::Vector3d> body_pos_err_d;
    InternalStateField<lin::Vector3d> body_velocity_d;



    
    // eventually not needed, just was for debug
    float inc_dir = 0;

    // not real control laws, just cool
    void tvc();

    
};

#endif
