#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

namespace PAN {
    // Environment-based initializations of the control loop time.
    // control_cycle_time is the value actually used for timing. The
    // other constants are just informational.
    constexpr unsigned int control_cycle_time_ms = 120;
    constexpr unsigned int control_cycle_time_us = 120000;
    constexpr unsigned int control_cycle_time = 120000;
}

/**
 * @brief A set of constants for the Servo CT
 * 
 */
namespace SERVO {

    constexpr unsigned char flap1_pin = 29;
    constexpr unsigned char flap2_pin = 30;
    constexpr unsigned char flap3_pin = 31;
    constexpr unsigned char flap4_pin = 32;
}

#endif
