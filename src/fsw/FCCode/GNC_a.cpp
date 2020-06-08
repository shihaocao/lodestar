#include "GNC_a.hpp"
#include <gnc/utilities.hpp>


GNC_a::GNC_a(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "gnc_a", offset),
    fin_commands_f("gnc_a.fin_cmds"),
    glob_acc_vec_f("imu.glob_acc_vec")

    {
        add_internal_field(fin_commands_f);
        add_internal_field(glob_acc_vec_f);
        

        mission_mode_fp = find_internal_field<unsigned char>("ls.mode", __FILE__, __LINE__);
        omega_vec_fp = find_internal_field<lin::Vector3f>("imu.gyr_vec", __FILE__, __LINE__);
        acc_vec_fp = find_internal_field<lin::Vector3f>("imu.acc_vec", __FILE__, __LINE__);
        grav_vec_fp = find_internal_field<lin::Vector3f>("imu.grav_vec", __FILE__, __LINE__);
        net_acc_vec_fp = find_internal_field<lin::Vector3f>("imu.net_acc_vec", __FILE__, __LINE__);
        euler_vec_fp = find_internal_field<lin::Vector3f>("imu.euler_vec", __FILE__, __LINE__);
        quat_fp = find_internal_field<lin::Vector4d>("imu.quat", __FILE__, __LINE__);
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
    }



void GNC_a::execute(){

    mission_mode_t mode = static_cast<mission_mode_t>(mission_mode_fp->get());

    switch(mode) {
        case mission_mode_t::starhopper:
             tvc();
            break;
        
        default:
            printf(debug_severity::error, "Master state not defined: %d\n", static_cast<unsigned int>(mode));
            // mission_mode_fp->set(static_cast<unsigned char>(mission_mode_t::landed));
            break;
    }

}


void GNC_a::tvc(){
    
    lin::Vector4f fin_commands = fin_commands_f.get();
    lin::Vector3d net_acc_vec_d = net_acc_vec_fp->get();
    lin::Vector3d glob_acc_vec_d = glob_acc_vec_f.get();
    
    
    
    /*
    Serial.print("x:");
    Serial.println(omega_vec_fp->get()(0));
    Serial.print("y:");
    Serial.println(omega_vec_fp->get()(1));
    Serial.print("z:");
    Serial.println(omega_vec_fp->get()(2));
    

   
    Serial.print("(");
    Serial.print(quat_fp->get()(0));
    Serial.print(", ");
    Serial.print(quat_fp->get()(1));
    Serial.print(", ");
    Serial.print(quat_fp->get()(2));
    Serial.print(", ");
    Serial.print(quat_fp->get()(3));
    Serial.println(")");
    */

    // testing
    lin::Vector4d frame_a_to_b{0.707,0.0,-0.707,0.0}; //idk?
    lin::Vector3d v_in_a{1.0,0.0,0.0}; 
    lin::Vector3d v_in_b{0.0,0.0,0.0};
    
    gnc::utl::quat_conj(frame_a_to_b);

    gnc::utl::rotate_frame(frame_a_to_b, v_in_a, v_in_b);
    

    //Converts acceleration in body frame to acceleration in global frame
    gnc::utl::rotate_frame(quat_fp->get(), net_acc_vec_d, glob_acc_vec_d);

    
    
    Serial.print("(");
    Serial.print(net_acc_vec_d(0));
    Serial.print(", ");
    Serial.print(net_acc_vec_d(1));
    Serial.print(", ");
    Serial.print(net_acc_vec_d(2));
    Serial.print(")");
    

    Serial.print("      (");
    Serial.print(glob_acc_vec_d(0));
    Serial.print(", ");
    Serial.print(glob_acc_vec_d(1));
    Serial.print(", ");
    Serial.print(glob_acc_vec_d(2));
    Serial.println(")");
    

    //No Control Method (Simply Sets Servos to Angle of Gyro)

    /*
    fin_commands(0)=(euler_vec_fp->get()(1));
    fin_commands(1)=-(euler_vec_fp->get()(2));
    fin_commands(2)=(euler_vec_fp->get()(2));
    fin_commands(3)=-(euler_vec_fp->get()(1));
    */


    fin_commands_f.set(fin_commands);
}

