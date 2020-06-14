#include "GNC_a.hpp"
#include <gnc/utilities.hpp>


GNC_a::GNC_a(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc_a", offset),
    fin_commands_f("gnc_a.fin_cmds"),
    glob_acc_vec_f("imu.glob_acc_vec"),
    thrust_commands_f("gnc_a.thrust_cmds"),
    setpoint_d("gnc_a.setpoint"),
    velocity_d("gnc_a.velocity"),
    position_d("gnc_a.position"),
    glob_pos_err_d("gnc_a.glob_pos_err"),
    body_pos_err_d("gnc_a.body_pos_err"),
    body_velocity_d("gnc_a.body_velocity")
    

    {
        add_internal_field(fin_commands_f);
        add_internal_field(glob_acc_vec_f);
        add_internal_field(thrust_commands_f);
        add_internal_field(setpoint_d);
        add_internal_field(velocity_d);
        add_internal_field(position_d);
        add_internal_field(glob_pos_err_d);
        add_internal_field(body_pos_err_d);
        add_internal_field(body_velocity_d);


        mission_mode_fp = find_internal_field<unsigned char>("ls.mode", __FILE__, __LINE__);
        omega_vec_fp = find_internal_field<lin::Vector3f>("imu.gyr_vec", __FILE__, __LINE__);
        acc_vec_fp = find_internal_field<lin::Vector3f>("imu.acc_vec", __FILE__, __LINE__);
        grav_vec_fp = find_internal_field<lin::Vector3f>("imu.grav_vec", __FILE__, __LINE__);
        lin_acc_vec_fp = find_internal_field<lin::Vector3f>("imu.linear_acc_vec", __FILE__, __LINE__);
        acc_error_fp = find_internal_field<lin::Vector3f>("ls.acc_error", __FILE__, __LINE__);     
        euler_vec_fp = find_internal_field<lin::Vector3f>("imu.euler_vec", __FILE__, __LINE__);
        quat_fp = find_internal_field<lin::Vector4d>("imu.quat", __FILE__, __LINE__);
        init_quat_dp = find_internal_field<lin::Vector4d>("ls.init_quat", __FILE__, __LINE__);
        quat_inv_fp = find_internal_field<lin::Vector4d>("imu.quat_inv", __FILE__, __LINE__);
     
        // default all fins to no actuation
        fin_commands_f.set({
            0.0,
            0.0,
            0.0,
            0.0,
        });

        glob_acc_vec_f.set({
            0.0,
            0.0,
            0.0,
        });

        // default motor to no thrust
        thrust_commands_f.set({
            0.0,
            0.0,
        });
    
        

    }


void GNC_a::execute(){

    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_fp->get());

    switch(mode) {
        case mission_mode_t::starhopper1:
             setpoint_d.set(CONTROLS::setpoint_1);
             tvc();
            break;
        case mission_mode_t::starhopper2:
             setpoint_d.set(CONTROLS::setpoint_2);
             tvc();
            break;
        case mission_mode_t::starhopper3:
             setpoint_d.set(CONTROLS::setpoint_3);
             tvc();
            break;
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            // mission_mode_fp->set(static_cast<unsigned char>(mission_mode_t::landed));
            break;
    }

}

void quat_conj(lin::Vector4d const &q, lin::Vector4d &res) {
  res = {q(0), -q(1), -q(2), q(3) };
}

void hamilton_product(lin::Vector4d const &q, lin::Vector4d const &r,
    lin::Vector4d &res) {
    res(0)=(r(0)*q(0)-r(1)*q(1)-r(2)*q(2)-r(3)*q(3));
    res(1)=(r(0)*q(1)+r(1)*q(0)-r(2)*q(3)+r(3)*q(2));
    res(2)=(r(0)*q(2)+r(1)*q(3)+r(2)*q(0)-r(3)*q(1));
    res(3)=(r(0)*q(3)-r(1)*q(2)+r(2)*q(1)+r(3)*q(0));
}


void rotate_frame(lin::Vector4d const &q, lin::Vector3d const &v, lin::Vector3d &res){
   lin::Vector4d q_v= {0.0,v(0),v(1),v(2)};
   lin::Vector4d intermediate = {0.0,0.0,0.0,0.0};
   lin::Vector4d q_res = {0.0,0.0,0.0,0.0};
   lin::Vector4d q_conj = {0.0,0.0,0.0,0.0};
   quat_conj(q,q_conj);
   hamilton_product(q,q_v,intermediate);
   hamilton_product(intermediate,q_conj,q_res);
   res(0)=q_res(1);
   res(1)=q_res(2);
   res(2)=q_res(3);
}



void GNC_a::tvc(){
    //Converting Statefields into tangible vectors
    lin::Vector4f fin_commands = fin_commands_f.get();
    lin::Vector2f thrust_commands = thrust_commands_f.get();
    lin::Vector3d position = position_d.get();
    lin::Vector3d velocity = velocity_d.get();
    lin::Vector3d lin_acc_vec_d = lin_acc_vec_fp->get();
    lin::Vector3d glob_acc = glob_acc_vec_f.get();
    lin::Vector3d body_velocity = body_velocity_d.get();
    lin::Vector3d setpoint = setpoint_d.get();
    lin::Vector4d quat = quat_fp->get();


    lin::Vector4d init_quat = init_quat_dp->get();
    lin::Vector4d init_quat_conj = {0.0,0.0,0.0,0.0};
    lin::Vector4d quat_inv = {0.0,0.0,0.0,0.0};
    quat_conj(quat,quat_inv);
    quat_conj(init_quat,init_quat_conj);
    lin::Vector4d net_quat_conj = {0.0,0.0,0.0,0.0};
    lin::Vector4d net_quat = {0.0,0.0,0.0,0.0};

    //Creates the quaternion to rotate about to go from body frame to equilibrium global frame
    hamilton_product(init_quat_conj,quat,net_quat);

    //Creates quaternion to rotate about to go from equilibrium global frame to body frame
    quat_conj(net_quat,net_quat_conj);



    //Calculates Position via numerical integration
    position_d.set({
        position(0)+velocity(0)*PAN::control_cycle_time_ms/1000+0.5*glob_acc(0)*PAN::control_cycle_time_ms/1000*PAN::control_cycle_time_ms/1000,
        position(1)+velocity(1)*PAN::control_cycle_time_ms/1000+0.5*glob_acc(1)*PAN::control_cycle_time_ms/1000*PAN::control_cycle_time_ms/1000,
        position(2)+velocity(2)*PAN::control_cycle_time_ms/1000+0.5*glob_acc(2)*PAN::control_cycle_time_ms/1000*PAN::control_cycle_time_ms/1000,
    });

    //Calculates Velocity via numerical integration
    velocity_d.set({
        velocity(0)+glob_acc(0)*PAN::control_cycle_time_ms/1000,
        velocity(1)+glob_acc(1)*PAN::control_cycle_time_ms/1000,
        velocity(2)+glob_acc(2)*PAN::control_cycle_time_ms/1000,
        });


    //Converts acceleration in body frame to acceleration in global frame (accounts for the boot quat not being (1,0,0,0))
    rotate_frame(net_quat, lin_acc_vec_d, glob_acc);


    //Sets the value of global acceleration while accounting for any bias in the IMU acceleration readings
    glob_acc_vec_f.set({
        glob_acc(0),//-acc_error_fp->get()(0),
        glob_acc(1),//-acc_error_fp->get()(1),
        glob_acc(2)//-acc_error_fp->get()(2),
    });

    //Sets global position error
    glob_pos_err_d.set({
        setpoint(0)-position_d.get()(0),
        setpoint(1)-position_d.get()(1),
        setpoint(2)-position_d.get()(2),
    });

    //Formats vectors for quaternion rotation
    lin::Vector3d glob_pos_err = glob_pos_err_d.get();
    lin::Vector3d body_pos_err = {0.0,0.0,0.0};

    //Rotates global position error by the orientation quaternion to get body position error
    rotate_frame(net_quat_conj, glob_pos_err, body_pos_err);

    //Sets the value of the body position error vector
    body_pos_err_d.set({
        body_pos_err(0),
        body_pos_err(1),
        body_pos_err(2),
    });

    //Rotates global velocity vector by the orientation quaternion to get body velocity vector
    rotate_frame(net_quat_conj, velocity, body_velocity);
    //Sets body velocity vector
    body_velocity_d.set({
        body_velocity(0),
        body_velocity(1),
        body_velocity(2),
    });

    //Creates a normalized body error vector. It has two entries. Error along all but the vertical axis.
    //This is how the direction of tilt for position control is determined. Still not finished yet
    lin::Vector2d body_pos_err_norm {
        body_pos_err(1)/CONTROLS::max_position_error,
        body_pos_err(2)/CONTROLS::max_position_error
        }; 

    
    Serial.print("(");
    Serial.print(net_quat(0));
    Serial.print(", ");
    Serial.print(net_quat(1));
    Serial.print(", ");
    Serial.print(net_quat(2));
    Serial.print(", ");
    Serial.print(net_quat(3));
    Serial.print(")");

    Serial.print("      (");
    Serial.print(lin_acc_vec_d(0));
    Serial.print(", ");
    Serial.print(lin_acc_vec_d(1));
    Serial.print(", ");
    Serial.print(lin_acc_vec_d(2));
    Serial.print(")");

    Serial.print("      (");
    Serial.print(glob_acc(0));
    Serial.print(", ");
    Serial.print(glob_acc(1));
    Serial.print(", ");
    Serial.print(glob_acc(2));
    Serial.println(")");
    


    //No Control Method (Simply Sets Servos to Angle of Gyro)

    /*
    fin_commands(0)=(euler_vec_fp->get()(1));
    fin_commands(1)=-(euler_vec_fp->get()(2));
    fin_commands(2)=(euler_vec_fp->get()(2));
    fin_commands(3)=-(euler_vec_fp->get()(1));
    */


    fin_commands_f.set(fin_commands);
    thrust_commands_f.set(thrust_commands);


    
    


   
}

