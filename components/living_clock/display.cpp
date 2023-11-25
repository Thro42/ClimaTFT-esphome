#include <SPI.h>
#include <time.h>                   // time() ctime(
#include <AsyncDelay.h>
#include "display.h"
#include <lvgl.h>
#include "ui.h"
#include <Arduino_GFX_Library.h>

/****************************************************************************************************/
#define GFX_BL 2
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
    9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
    15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */,
    0 /* hsync_polarity */, 180 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
    0 /* vsync_polarity */, 12 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */);
Arduino_RGB_Display *lcd = new Arduino_RGB_Display(
    800 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */);
/****************************************************************************************************/
/* Screen Saver Settings*/
#define TFT_BL 2
TimerHandle_t screenSaverTimer;

/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[800 * 480 / 10];      //5,7inch: lv_color_t disp_draw_buf[800*480/10]            4.3inch: lv_color_t disp_draw_buf[480*272/10]
static lv_disp_drv_t disp_drv;

AsyncDelay delay_1s;

void setupDisplay() {
  // Init Display
  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  lv_init();

  delay(100);

  screenWidth = lcd->width();
  screenHeight = lcd->height();

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);
  //  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, 480 * 272 / 10);
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);

  ui_init();//ui from Squareline or GUI Guider

/* Screen Saver Setup*/
#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  ledcSetup(0 /* LEDChannel */, 5000 /* freq */, 8 /* resolution */);
  ledcAttachPin(TFT_BL, 0 /* LEDChannel */);
  ledcWrite(0 /* LEDChannel */, 127); /* 0-255 */
  screenSaverTimer = xTimerCreate("saverTimer", pdMS_TO_TICKS(14000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(screenSaver));
  xTimerStart(screenSaverTimer, 0);
#endif

  delay_1s.start(5000, AsyncDelay::MILLIS);
}

/*******************************************************************************/
void loopDisplay() {
  lv_timer_handler();
  if (delay_1s.isExpired()) {
      showLocalTime();
      delay_1s.repeat();
  } 
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
  lv_disp_flush_ready(disp);
}
/*******************************************************************************/
void screenSaver() {
  Serial.println("Screensaver...");
  //digitalWrite(TFT_BL, LOW);
  ledcWrite(0 /* LEDChannel */, 1); /* 0-255 */
}
/*******************************************************************************/
void setPresence( bool presence) {
  if(presence) {
    xTimerStop(screenSaverTimer, 0);
    //digitalWrite(TFT_BL, HIGH);
    ledcWrite(0 /* LEDChannel */, 127); /* 0-255 */
    xTimerStart(screenSaverTimer, 0);
  } else {
//      digitalWrite(TFT_BL, LOW);
  }
}
/*******************************************************************************/
void showLocalTime() {
  struct tm timeinfo;
  char buffer[20];
  if (!getLocalTime(&timeinfo)) {
    Serial.println( "Get Time faild" );
    return;
  }
  Serial.println(&timeinfo, "%H:%M");
  strftime(buffer, sizeof buffer, "%H:%M", &timeinfo); 
  lv_label_set_text(ui_Time, buffer);
}
/*******************************************************************************/
void outBrasilTime( String newTime) {
  char buffer[10];
  sprintf(buffer, "%s", newTime);
  Serial.println(buffer);
  lv_label_set_text(ui_LblBrTime, buffer);

}
/*******************************************************************************/
void outInTemp( String newTemp) {
  char buffer[10];
  float temp = newTemp.toFloat();
  sprintf(buffer, "%02.1f", temp);
  Serial.println(buffer);
  lv_label_set_text(ui_lblInTemp, buffer);

}

/*******************************************************************************/
void outInHumidity( String newHuni){
  char buffer[10];
  float hum = newHuni.toFloat();
  sprintf(buffer, "%02.0f%%", hum);
  Serial.println(buffer);
  lv_label_set_text(ui_lblInHumi, buffer);
}

/*******************************************************************************/
void outOutTemp( String newTemp){
  char buffer[10];
  float temp = newTemp.toFloat();
  sprintf(buffer, "%02.1f", temp);
  Serial.println(buffer);
  lv_label_set_text(ui_lblOutTemp, buffer);
}
