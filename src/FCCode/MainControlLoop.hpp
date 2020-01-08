#ifndef MAIN_CONTROL_LOOP_TASK_HPP_
#define MAIN_CONTROL_LOOP_TASK_HPP_

#include "ControlTask.hpp"
#include <StateField.hpp>
#include <StateFieldRegistry.hpp>

#include "ClockManager.hpp"
#include "FieldCreatorTask.hpp"
#include "IMUMonitor.hpp"
#include "BMPMonitor.hpp"
#include "LEDControlTask.hpp"
#include "MissionManager.hpp"

class MainControlLoop : public ControlTask<void> {
   protected:
    FieldCreatorTask field_creator_task;
    ClockManager clock_manager;

    Adafruit_BNO055 imu;
    IMUMonitor imu_monitor;

    Adafruit_BMP280 bmp;
    BMPMonitor bmp_monitor;

    LEDControlTask led_control_task;

    MissionManager mission_manager;

    

    // Control cycle time offsets, in microseconds
    #ifdef FUNCTIONAL_TEST
    // https://cornellprod-my.sharepoint.com/:x:/r/personal/saa243_cornell_edu/_layouts/15/Doc.aspx?sourcedoc=%7B04C55BBB-7AED-410B-AC43-67352393D6D5%7D&file=Flight%20Software%20Cycle.xlsx&action=default&mobileredirect=true&cid=e2b9bd89-7037-47bf-ad2a-fd8b25808939
        static constexpr unsigned int debug_task_offset          =   5500;
        static constexpr unsigned int piksi_control_task_offset  =  55000;
        static constexpr unsigned int imu_monitor_offset         =  70500;
        static constexpr unsigned int attitude_estimator_offset  =  85500;
        static constexpr unsigned int gomspace_controller_offset = 106500;
        static constexpr unsigned int uplink_consumer_offset     = 111500;
        static constexpr unsigned int mission_manager_offset     = 111600;
        static constexpr unsigned int docking_controller_offset  = 152400;
        static constexpr unsigned int downlink_producer_offset   = 153400;
        static constexpr unsigned int quake_manager_offset       = 153500;
    #else
        static constexpr unsigned int debug_task_offset          =   3000;
        static constexpr unsigned int piksi_control_task_offset  =   4000;
        static constexpr unsigned int imu_monitor_offset         =   5000;
        static constexpr unsigned int bmp_monitor_offset         =   6000;
        static constexpr unsigned int attitude_estimator_offset  =  35500;
        static constexpr unsigned int gomspace_controller_offset =  56500;
        static constexpr unsigned int uplink_consumer_offset     =  61500;
        static constexpr unsigned int mission_manager_offset     =  61600;
        static constexpr unsigned int led_control_task_offset    =  80000;
        static constexpr unsigned int docking_controller_offset  = 103400;
        static constexpr unsigned int downlink_producer_offset   = 104400;
        static constexpr unsigned int quake_manager_offset       = 104500;
        
    #endif

    /**
     * @brief Total memory use, in bytes.
     */

   public:
    /*
     * @brief Construct a new Main Control Loop Task object
     * 
     * @param registry State field registry
     * @param flow_data Metadata for telemetry flows.
     */
    MainControlLoop(StateFieldRegistry& registry);

    /**
     * @brief Processes state field commands present in the serial buffer.
     */
    void execute() override;

};

#endif