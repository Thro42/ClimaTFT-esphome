#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"

namespace esphome
{
    namespace  living_clock_hub
    {
        class LivingClockHub : public Component {

            void setup() override;
            void dump_config() override;
            void loop() override;
            //
            set_out_temp(float new_temp);
            set_in_temp(float new_temp);
            set_in_humitity(float new_hum);
            set_main_time(ESPTime time);
            set_extern_time(ESPTime time);
        }
    }
}