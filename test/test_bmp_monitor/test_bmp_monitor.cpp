#include "../StateFieldRegistryMock.hpp"

#include <Wire.h>
#include <Adafruit_Sensor.h>
    
#include "../../src/FCCode/BMPMonitor.hpp"
#include "adcs_constants.hpp"

#include <unity.h>

class TestFixture {
    public:
        StateFieldRegistryMock registry;

        // pointers to output statefields for easy access
        InternalStateField<sensors_event_t>* temp_fp;
        InternalStateField<sensors_event_t>* pressure_fp;

        //pointer to control task
        std::unique_ptr<BMPMonitor> bmp_monitor;

        Adafruit_BMP280 bmp;
        
        // Create a TestFixture instance of AttitudeEstimator with pointers to statefields
        TestFixture() : registry(), bmp(){

            bmp_monitor = std::make_unique<BMPMonitor>(registry, 0, bmp);  

            // initialize pointers to statefields
            //lin_acc_vec_fp = registry.find_readable_field_t<f_vector_t>("adcs_monitor.rwa_speed_rd");
            temp_fp = registry.find_internal_field_t<sensors_event_t>("bmp.temp");
            pressure_fp = registry.find_internal_field_t<sensors_event_t>("bmp.pressure");
        }
};

//checks that all ref vector and actual vector are pretty much the same
void elements_same(const std::array<float, 3> ref, const std::array<float, 3> actual){
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[0], actual[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[1], actual[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, ref[2], actual[2]);
}

void printEvent(const sensors_event_t& event) {
    float x = -1000000.0f; //dumb values, easy to spot problem
    if (event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE) {
        x = event.temperature;
        Serial.printf("Temp (C): %f\n", x);
    }
    else if (event.type == SENSOR_TYPE_PRESSURE) {
        x = event.pressure;
        Serial.printf("Pressure (Pa): %f\n", x*BMPMonitor::hPa_to_Pa);

    }
    
    //these just check that the values were read to something
    //please use something else for sanity check, eyes?
    TEST_ASSERT_NOT_EQUAL(-1000000, x);

}

void test_task_initialization()
{
    TestFixture tf;
}

void test_execute(){
    TestFixture tf;

    tf.bmp_monitor->execute();

    printEvent(tf.temp_fp->get());
    printEvent(tf.pressure_fp->get());
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