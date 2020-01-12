#include "../StateFieldRegistryMock.hpp"

#include <Wire.h>
#include <Adafruit_Sensor.h>
    
#include "../../src/FCCode/IMUMonitor.hpp"

#include "../custom_assertions.hpp"

#include <unity.h>

class TestFixture {
    public:
        StateFieldRegistryMock registry;

        // pointers to output statefields for easy access
        InternalStateField<f_vector_t>* linear_acc_vec_fp;
        InternalStateField<f_vector_t>* acc_vec_fp;
        InternalStateField<f_vector_t>* grav_vec_fp;
        InternalStateField<f_vector_t>* euler_vec_fp;
        InternalStateField<f_vector_t>* gyr_vec_fp;
        InternalStateField<f_vector_t>* mag_vec_fp;

        //pointer to control task
        std::unique_ptr<IMUMonitor> imu_monitor;

        Adafruit_BNO055 imu;
        
        // Create a TestFixture instance of AttitudeEstimator with pointers to statefields
        TestFixture() : registry(), imu(55, 0x28){

            imu_monitor = std::make_unique<IMUMonitor>(registry, 0, imu);  

            // initialize pointers to statefields
            //lin_acc_vec_fp = registry.find_readable_field_t<f_vector_t>("adcs_monitor.rwa_speed_rd");
            linear_acc_vec_fp = registry.find_internal_field_t<f_vector_t>("imu.linear_acc_vec");
            acc_vec_fp = registry.find_internal_field_t<f_vector_t>("imu.acc_vec");
            grav_vec_fp = registry.find_internal_field_t<f_vector_t>("imu.grav_vec");
            euler_vec_fp = registry.find_internal_field_t<f_vector_t>("imu.euler_vec");
            gyr_vec_fp = registry.find_internal_field_t<f_vector_t>("imu.gyr_vec");
            mag_vec_fp = registry.find_internal_field_t<f_vector_t>("imu.mag_vec");
        }
};

//checks that all ref vector and actual vector are pretty much the same
void elements_same(const std::array<float, 3> ref, const std::array<float, 3> actual){
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[0], actual[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[1], actual[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[2], actual[2]);
}

void print_f_vec(const f_vector_t& input) {

    Serial.printf("%f, %f, %f\n",
        input[0],
        input[1],
        input[2]);

}

void test_task_initialization()
{
    TestFixture tf;
}

void test_execute(){
    TestFixture tf;

    tf.imu_monitor->execute();

    Serial.printf("Linear_Acc: ");
    print_f_vec(tf.linear_acc_vec_fp->get());
    PAN_TEST_ASSERT_EQUAL_FLOAT_VEC(f_vector_t({5,5,5}).data(), tf.linear_acc_vec_fp->get(), 10)

    Serial.printf("Acc: ");
    print_f_vec(tf.acc_vec_fp->get());

    Serial.printf("Grav: ");
    print_f_vec(tf.grav_vec_fp->get());

    Serial.printf("Euler: ");
    print_f_vec(tf.euler_vec_fp->get());

    Serial.printf("Gyr: ");
    print_f_vec(tf.gyr_vec_fp->get());

    Serial.printf("Mag: ");
    print_f_vec(tf.mag_vec_fp->get());
}

int test_control_task()
{
        UNITY_BEGIN();
        RUN_TEST(test_task_initialization);
        RUN_TEST(test_execute);
        return UNITY_END();
}

//for lodestar we won't run tests in desktop? idk
#ifdef DESKTOP
int main()
{
        return test_control_task();
}
#else
#include <Arduino.h>
void setup()
{
        delay(2000);
        Serial.begin(9600);
        test_control_task();
}

void loop() {}
#endif