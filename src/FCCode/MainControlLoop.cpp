#include "MainControlLoop.hpp"
#include "constants.hpp"


MainControlLoop::MainControlLoop(StateFieldRegistry& registry)
    : ControlTask<void>(registry), 
      field_creator_task(registry),
      clock_manager(registry, PAN::control_cycle_time),
      imu(55, 0x28),
      imu_monitor(registry, imu_monitor_offset, imu),
      bmp_monitor(registry, bmp_monitor_offset, bmp),
      led_control_task(registry, led_control_task_offset),
      mission_manager(registry, mission_manager_offset) // This item is initialized last so it has access to all state fields
{
    //setup I2C bus for Flight Controller
    // #ifndef DESKTOP
    // Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000, I2C_OP_MODE_IMM);
    // #endif

}

void MainControlLoop::execute() {
    clock_manager.execute();
    imu_monitor.execute_on_time();
    bmp_monitor.execute_on_time();
    mission_manager.execute_on_time();
    led_control_task.execute_on_time();
    
}