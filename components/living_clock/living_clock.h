#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"
#include "esphome/components/output/float_output.h"

namespace esphome
{
    namespace  living_clock
    {
        struct Clock {
            esphome::output::FloatOutput *out_temp;
            esphome::output::FloatOutput *in_temp;
            esphome::output::FloatOutput *in_huminity;
        }
        class LivingClockHub : public Component {
            public:
                void setup() override;
                void dump_config() override;
                void loop() override;
                //
                void add_clock(const Clock &clock) { clock_.push_back(clock); }
                //
                set_out_temp(float new_temp);
                set_in_temp(float new_temp);
                set_in_humitity(float new_hum);
                set_main_time(ESPTime time);
                set_extern_time(ESPTime time);
            protected:
                std::vector<Clock> clock_;
        }
    }
}