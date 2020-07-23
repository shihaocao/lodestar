#include "SDCardControlTask.hpp"

SDCardControlTask::SDCardControlTask(StateFieldRegistry &registry, 
    unsigned int offset)
    : TimedControlTask<void>(registry, "sd_card_control_task", offset)
    {
        flap_commands_fp = find_internal_field<lin::Vector4f>("gnc.flap_cmds", __FILE__, __LINE__);
        servo_on_fp = find_internal_field<bool>("ls.servo_on", __FILE__, __LINE__);

        fin_commands_fp = find_internal_field<lin::Vector4f>("gnc_a.fin_cmds", __FILE__, __LINE__);

        SD.begin(chipSelect);
        myFile = SD.open("data.txt", FILE_WRITE);
        
    }

void SDCardControlTask::execute(){
    if(myFile){
        myFile.printf("CCNO BLAH BLAH BLAH: %u\n", control_cycle_count);
        myFile.printf("CCNO BLAH BLAH BLAH: %u\n", control_cycle_count);
        myFile.printf("CCNO BLAH BLAH BLAH: %u\n", control_cycle_count);
        myFile.printf("CCNO BLAH BLAH BLAH: %u\n", control_cycle_count);
        myFile.printf("CCNO BLAH BLAH BLAH: %u\n", control_cycle_count);
        myFile.printf("CCNO BLAH BLAH BLAH: %u\n", control_cycle_count);
    }
    myFile.flush();
}

void SDCardControlTask::actuate(){

}