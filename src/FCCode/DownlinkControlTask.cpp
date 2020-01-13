#include "DownlinkControlTask.hpp"

DownlinkControlTask::DownlinkControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        altitude_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);
        euler_fp = find_internal_field<f_vector_t>("imu.euler_vec", __FILE__, __LINE__);
        acc_fp = find_internal_field<f_vector_t>("imu.acc_vec", __FILE__, __LINE__);

        #ifdef SERIAL_DEBUG
        Serial.begin(9600);
        #endif
    }

void DownlinkControlTask::execute(){

    #ifdef SERIAL_DEBUG
    Serial.printf("Altitude (m): %f\n", altitude_fp->get());

    f_vector_t euler_read;
    euler_read = euler_fp->get();
    Serial.printf("Euler: %f, %f, %f\n", euler_read[0], euler_read[1], euler_read[2]);

    f_vector_t acc_read;
    acc_read = acc_fp->get();
    Serial.printf("Acc: %f, %f, %f\n", acc_read[0], acc_read[1], acc_read[2]);
    #endif
}