#include "../StateFieldRegistryMock.hpp"

//#include <cmath>
//#include <math.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
    
#include "../../src/FCCode/IMUMonitor.hpp"
#include "adcs_constants.hpp"

#include <unity.h>

class TestFixture {
    public:
        StateFieldRegistryMock registry;

        // pointers to output statefields for easy access
        InternalStateField<sensors_event_t>* linear_acc_vec_fp;
        InternalStateField<sensors_event_t>* acc_vec_fp;
        InternalStateField<sensors_event_t>* grav_vec_fp;
        InternalStateField<sensors_event_t>* euler_vec_fp;
        InternalStateField<sensors_event_t>* gyr_vec_fp;
        InternalStateField<sensors_event_t>* mag_vec_fp;

        //pointer to control task
        std::unique_ptr<IMUMonitor> imu_monitor;

        Adafruit_BNO055 imu;
        
        // Create a TestFixture instance of AttitudeEstimator with pointers to statefields
        TestFixture() : registry(), imu(55, 0x28){

            imu_monitor = std::make_unique<IMUMonitor>(registry, 0, imu);  

            // initialize pointers to statefields
            //lin_acc_vec_fp = registry.find_readable_field_t<f_vector_t>("adcs_monitor.rwa_speed_rd");
            linear_acc_vec_fp = registry.find_internal_field_t<sensors_event_t>("imu.linear_acc");
            acc_vec_fp = registry.find_internal_field_t<sensors_event_t>("imu.acc_vec");
            grav_vec_fp = registry.find_internal_field_t<sensors_event_t>("imu.grav_vec");
            euler_vec_fp = registry.find_internal_field_t<sensors_event_t>("imu.euler_vec");
            gyr_vec_fp = registry.find_internal_field_t<sensors_event_t>("imu.gyr_vec");
            mag_vec_fp = registry.find_internal_field_t<sensors_event_t>("imu.mag_vec");
        }
};

//checks that all ref vector and actual vector are pretty much the same
void elements_same(const std::array<float, 3> ref, const std::array<float, 3> actual){
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[0], actual[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[1], actual[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[2], actual[2]);
}

void printEvent(const sensors_event_t event) {
    Serial.println();
    Serial.print(event.type);
    double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
    if (event.type == SENSOR_TYPE_ACCELEROMETER) {
        x = event.acceleration.x;
        y = event.acceleration.y;
        z = event.acceleration.z;
    }
    else if (event.type == SENSOR_TYPE_ORIENTATION) {
        x = event.orientation.x;
        y = event.orientation.y;
        z = event.orientation.z;
    }
    else if (event.type == SENSOR_TYPE_MAGNETIC_FIELD) {
        x = event.magnetic.x;
        y = event.magnetic.y;
        z = event.magnetic.z;
    }
    else if ((event.type == SENSOR_TYPE_GYROSCOPE) || (event.type == SENSOR_TYPE_ROTATION_VECTOR)) {
        x = event.gyro.x;
        y = event.gyro.y;
        z = event.gyro.z;
    }
    
    //these just check that the values were read to something
    //please use something else for sanity check, eyes?
    TEST_ASSERT_NOT_EQUAL(-1000000, x);
    TEST_ASSERT_NOT_EQUAL(-1000000, y);
    TEST_ASSERT_NOT_EQUAL(-1000000, z);

    Serial.print(": x= ");
    Serial.print(x);
    Serial.print(" | y= ");
    Serial.print(y);
    Serial.print(" | z= ");
    Serial.println(z);
}

void test_task_initialization()
{
    TestFixture tf;
}

void test_execute(){
    TestFixture tf;

    tf.imu_monitor->execute();

    printEvent(tf.linear_acc_vec_fp->get());
    printEvent(tf.acc_vec_fp->get());
    printEvent(tf.grav_vec_fp->get());
    printEvent(tf.euler_vec_fp->get());
    printEvent(tf.gyr_vec_fp->get());
    printEvent(tf.mag_vec_fp->get());
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