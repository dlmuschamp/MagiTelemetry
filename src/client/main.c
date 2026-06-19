#include <stdint.h>
#include <stdio.h>  // So I can use printf() to debug
#include <stdlib.h> // Standard types
#include <unistd.h> // For usleep()

#include "lv_conf.h"
#include "lvgl/include/lvgl/core/lv_obj_style.h"
#include "lvgl/include/lvgl/core/lv_obj_style_gen.h"
#include "lvgl/include/lvgl/display/lv_display.h"
#include "lvgl/include/lvgl/lv_types.h"
#include "lvgl/include/lvgl/widgets/lv_label.h"
#include "lvgl/lvgl.h"
#include "magi_ipc.h" // My custom logging macro

static const uint32_t HOR_RES = 400, VER_RES = 300;
static const unsigned int SLEEP_TIME_uSEC = 5000;

// find out pros and cons of unsigned ints.
static char *WINDOW_NAME = "Magi Display";
static const char *MAIN_SUBSYS = "MAIN";

int main(void) {

  lv_init();

  lv_display_t *primary_disp = lv_wayland_window_create(
      HOR_RES, VER_RES, WINDOW_NAME, NULL); // call back can be null

  if (primary_disp == NULL) {
    MAGI_LOG_ERROR(MAIN_SUBSYS,
                   "New window pointer is null. Hyprland rejected the window.");
    return -1;
  }

  // grab active screen canvas
  lv_obj_t *active_screen = lv_screen_active();

  // set active screen background to black
  lv_obj_set_style_bg_color(active_screen, lv_color_hex(0x000000),
                            LV_PART_MAIN);

  // creating a text label and attaching it to the screen
  lv_obj_t *label = lv_label_create(active_screen);
  lv_label_set_text(label, "MAGI SYSTEM:\nAWAITING DATA....");

  // color the text magi orange
  lv_obj_set_style_text_color(label, lv_color_hex(0xFF9900), LV_PART_MAIN);

  // center the text
  lv_obj_center(label);

  printf("Graphics Engine Online. Rendering...\n");

  while (1) {
    lv_timer_handler();
    usleep(SLEEP_TIME_uSEC);
  }

  return 0;
}
