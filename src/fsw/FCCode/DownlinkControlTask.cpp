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
        quat_fp = find_internal_field<d_quat_t>("imu.quat", __FILE__, __LINE__);

        #if defined(HARDLINE)
        Serial.begin(9600);
        #endif

        #if defined(AIR)
        Serial1.begin(57600);
        #endif
    }

void DownlinkControlTask::execute(){

    #ifdef DL_OFF
    return;
    #endif

    #ifndef DL_OFF
    f_vector_t linear_acc_read = linear_acc_fp->get();
    f_vector_t acc_read = acc_fp->get();
    f_vector_t euler_read = euler_fp->get();
    f_vector_t gyr_read = gyr_fp->get();
    d_quat_t quat_read = quat_fp->get();
    #endif

    #ifdef AIR_TEST
    Serial1.print("0000;1111;2222;3333;4444;5555;6666;7777;8888;9999;0000,,,");
    return;
    #endif

    // unsigned int temp = PAN::control_cycle_time;
    #ifdef SPEED_TEST
    Serial.printf("CN: %u, CCT: %u\n", control_cycle_count, PAN::control_cycle_time_ms);
    #endif

    #if defined(AIR) && defined(COMPACT)
    airline_solo(control_cycle_count);
    airline_solo(altitude_fp->get());
    airline_compact(linear_acc_read);
    airline_compact(acc_read);
    airline_compact(euler_read);
    airline_compact(gyr_read);
    airline_compact(quat_read);
    Serial1.print("\n");
    #endif

    #if defined(HARDLINE) && defined(COMPACT)
    hardline_element(control_cycle_count);
    hardline_element(altitude_fp->get());
    hardline_compact(linear_acc_read);
    hardline_compact(acc_read);
    hardline_compact(euler_read);
    hardline_compact(gyr_read);
    hardline_compact(quat_read);
    Serial.print("\n");
    #endif

    #if defined(HARDLINE) && defined(FULL_DL)
    Serial.printf("Control Cycle Num: %u\n", control_cycle_count);
    Serial.printf("Altitude (m): %f\n", altitude_fp->get());
    Serial.printf("Linear Acc: %f, %f, %f\n", linear_acc_read[0], linear_acc_read[1], linear_acc_read[2]);
    Serial.printf("Acc: %f, %f, %f\n", acc_read[0], acc_read[1], acc_read[2]);
    Serial.printf("Euler: %f, %f, %f\n", euler_read[0], euler_read[1], euler_read[2]);
    Serial.printf("Gyr: %f, %f, %f\n", gyr_read[0], gyr_read[1], gyr_read[2]);
    Serial.print("\n");
    #endif

    #if defined(AIR) && defined(FULL_DL)
    Serial1.printf("Control Cycle Num: %u\n", control_cycle_count);
    Serial1.printf("Altitude (m): %f\n", altitude_fp->get());
    Serial1.printf("Linear Acc: %f, %f, %f\n", linear_acc_read[0], linear_acc_read[1], linear_acc_read[2]);
    Serial1.printf("Acc: %f, %f, %f\n", acc_read[0], acc_read[1], acc_read[2]);
    Serial1.printf("Euler: %f, %f, %f\n", euler_read[0], euler_read[1], euler_read[2]);
    Serial1.printf("Gyr: %f, %f, %f\n", gyr_read[0], gyr_read[1], gyr_read[2]);
    #endif
}