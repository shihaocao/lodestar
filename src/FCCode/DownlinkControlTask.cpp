#include "DownlinkControlTask.hpp"

DownlinkControlTask::DownlinkControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "downlink_control_task", offset)
    {
        altitude_fp = find_internal_field<float>("bmp.altitude", __FILE__, __LINE__);
        euler_fp = find_internal_field<f_vector_t>("imu.euler_vec", __FILE__, __LINE__);
        acc_fp = find_internal_field<f_vector_t>("imu.acc_vec", __FILE__, __LINE__);
        linear_acc_fp = find_internal_field<f_vector_t>("imu.linear_acc_vec", __FILE__, __LINE__);
        gyr_fp = find_internal_field<f_vector_t>("imu.gyr_vec", __FILE__, __LINE__);

        #ifdef SERIAL_DEBUG
        Serial.begin(9600);
        #endif
    }

void DownlinkControlTask::execute(){

    #ifdef SERIAL_DEBUG
    f_vector_t linear_acc_read;
    f_vector_t acc_read;
    f_vector_t euler_read;
    f_vector_t gyr_read;

    linear_acc_read = linear_acc_fp->get();
    acc_read = acc_fp->get();
    euler_read = euler_fp->get();
    gyr_read = gyr_fp->get();

    Serial.printf("Altitude (m): %f\n", altitude_fp->get());
    Serial.printf("Linear Acc: %f, %f, %f\n", linear_acc_read[0], linear_acc_read[1], linear_acc_read[2]);
    Serial.printf("Acc: %f, %f, %f\n", acc_read[0], acc_read[1], acc_read[2]);
    Serial.printf("Euler: %f, %f, %f\n", euler_read[0], euler_read[1], euler_read[2]);
    Serial.printf("Gyr: %f, %f, %f\n", gyr_read[0], gyr_read[1], gyr_read[2]);
    #endif
}