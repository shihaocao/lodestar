#ifndef MISSION_MANAGER_HPP_
#define MISSION_MANAGER_HPP_

#include "TimedControlTask.hpp"

#include "mission_mode_t.enum"
#include "adcs_mode_t.enum"

class MissionManager : public TimedControlTask<void> {
    public:

        MissionManager(StateFieldRegistry& registry, unsigned int offset);
    
        void execute() override;

    protected:

        void dispatch_warmup();
        void dispatch_initialization();
        void dispatch_standby();
        void dispatch_detumble();
        void dispatch_bellyflop();
        void dispatch_landed();

        // Fields that control overall mission state.
        /**
         * @brief Current mission mode (see mission_mode_t.enum)
         */
        InternalStateField<unsigned char> mission_mode_f;

};

#endif
