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