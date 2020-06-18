#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

namespace PAN {
    // Environment-based initializations of the control loop time.
    // control_cycle_time is the value actually used for timing. The
    // other constants are just informational.
    constexpr unsigned int control_cycle_time_ms = 100;
    constexpr unsigned int control_cycle_time_us = control_cycle_time_ms * 1000;
    constexpr unsigned int control_cycle_time = control_cycle_time_us;
}

namespace PINOUT {

    // let the GPS be connected to TX and RX 3
    // let the telemetry radio (57600 baud) be connected to TX1 and RX1

    // not actually a member variable, just putting it here
    #define GPSSerial Serial3

    
}

namespace MM {
    constexpr unsigned int warmup_millis = 10 * 1000;
    constexpr unsigned int init_millis = 10 * 1000;
    constexpr unsigned int init_cycles = 100;

    /**
     * @brief Terminate flight after N minutes. Automatically transition to landing.
     * 
     */
    constexpr unsigned int FTS_millis = 5 * 60 * 1000;

    /**
     * @brief If measure acceleration is below this threshold, we're in free fall.
     * 
     */
    constexpr float free_fall_thresh = 4.0;

    constexpr unsigned int consectuve_free_fall_cycles = 0;
    
    constexpr float detumble_thresh = 300.0; // rads per sec?
}
/**
 * @brief A set of constants for the Servo CT
 * 
 */
namespace SERVO {
    constexpr unsigned char num_flaps = 4;
    constexpr unsigned char flap1_pin = 29;
    constexpr unsigned char flap2_pin = 30;
    constexpr unsigned char flap3_pin = 35;
    constexpr unsigned char flap4_pin = 36;
    constexpr unsigned char fin1_pin = 2;
    constexpr unsigned char fin2_pin = 3;
    constexpr unsigned char fin3_pin = 22;
    constexpr unsigned char fin4_pin = 23;
    constexpr unsigned char motor1_pin = 4;
    constexpr unsigned char motor2_pin = 5;

    // bounds expected from GNC
    constexpr float servo_cmd_range = 90;
    constexpr float flap_cmd_min = 0;
    constexpr float flap_cmd_max = flap_cmd_min + servo_cmd_range;

    // bounds for the range for servo (limits on write microseconds)
    constexpr float servo_min = 0;
    constexpr float servo_max = 180;

    // how many degrees the servo is actually capable of
    constexpr float actual_range = 180;

    constexpr float servo_center = (servo_max - servo_min)/2.0;

    // range used for actual write microseconds
    constexpr float flap_write_min = servo_center - servo_cmd_range/2.0;
    constexpr float flap_write_max = servo_center + servo_cmd_range/2.0;

}

namespace CONTROLS{
    constexpr lin::Vector3d setpoint_1 {1.0,0.0,0.0}; //Setpoints in the hop
    constexpr lin::Vector3d setpoint_2 {1.0,3.0,3.0}; 
    constexpr lin::Vector3d setpoint_3 {0.0,3.0,3.0}; 


    constexpr double max_position_error = 5.0;
    constexpr double max_tilt = 3.0;
    constexpr double alph_pitch_max=5;
    constexpr double alph_yaw_max=5;
    constexpr double a_x_max=2;
    constexpr double weight=2; //Factor by which attitude control commands thrust
    constexpr double T_max=10; //Maximum thrust in Newtons
    constexpr double servo_max=20; //Measured from equilibrium


    constexpr double Kd_p_tilt = 1.5;
    constexpr double Kd_y_tilt = 1.5;
    constexpr double Kp_pitch = 1.1;
    constexpr double Ki_pitch = 0.01;
    constexpr double Kd_pitch = 0.5;
    constexpr double Kp_yaw = 1.1;
    constexpr double Ki_yaw = 0.01;
    constexpr double Kd_yaw = 0.5;

    //Ascent Gains
    constexpr double Kp_xa = 1.5;
    constexpr double Ki_xa = 0.8;
    constexpr double Kd_xa = 0.6;

    //Landing Gains
    constexpr double Kp_xd = 0.6;
    constexpr double Ki_xd = 0.0;
    constexpr double Kd_xd = 4;



}

#endif
