#include "esphome/core/log.h"
#include "esphome/core/time.h"
#include living_clock.h
#include "display.h"

namespace esphome
{
    namespace  living_clock
    {

        static const char *TAG = "living_clock_hub.component";

        void LivingClockHub::setup() {
            void setupDisplay()
        }
        void LivingClockHub::dump_config() {

        }
        void LivingClockHub::loop() {
             if (this->clock_.size() == 1) {
                auto &clock = this->clock_[0];
                if (clock.in_temp && clock.in_temp->has_state()) {
                    float temp = clock.in_temp->state;
                    outInTempFloat( temp );
                }                
             }
            void loopDisplay();
        }

        void LivingClockHub::set_out_temp(float new_temp) {
            String sTemp;
            char buff[10];
            sprintf(buff,"%02.1f",new_temp);
            sTemp = String(buff);
            void outOutTemp( sTemp)

        }
        void LivingClockHub::set_in_temp(float new_temp) {
            String sTemp;
            char buff[10];
            sprintf(buff,"%02.1f",new_temp);
            sTemp = String(buff);
            void outInTemp( sTemp)
        }
        void LivingClockHub::set_in_humitity(float new_hum) {

        }
        void ivingClockHub::set_main_time(ESPTime time) {

        }
        void ivingClockHub::set_extern_time(ESPTime time) {

        }
    }
}