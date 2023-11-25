#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include <lvgl.h>

void setupDisplay();
void loopDisplay();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

void screenSaver();
void setPresence( bool presence);

void showLocalTime();
void outBrasilTime( String newTime);
void outInTemp( String newTemp);
void outInHumidity( String newHuni);
void outOutTemp( String newTemp);
void setPresence( bool presence);

#endif // DISPLAY_H