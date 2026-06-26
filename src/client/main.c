// FILE: src/client/main.c
#include "../include/magi_ipc.h"
#include "lvgl/lvgl.h"
#include <stdio.h>
#include <unistd.h>

// Restored Globals (Stripped of Battery/Timer specific variables)
static const uint32_t HOR_RES = 1920, VER_RES = 1200;
static const unsigned int SLEEP_TIME_uSEC = 5000;
static char *WINDOW_NAME = "Magi Display";
static const char *MAIN_SUBSYS = "MAIN";

// Forward declaration from manager
extern void setup_main_ui(void);

int main(void) {
  lv_init();

  lv_display_t *primary_disp =
      lv_wayland_window_create(HOR_RES, VER_RES, WINDOW_NAME, NULL);

  if (primary_disp == NULL) {
    MAGI_LOG_ERROR(MAIN_SUBSYS,
                   "New window pointer is null. Hyprland rejected the window.");
    return -1;
  }

  // Build the UI via the manager (This will now also start the component
  // timers!)
  setup_main_ui();

  printf("Graphics Engine Online. Rendering...\n");

  // Main loop: Just keep the LVGL engine ticking
  while (1) {
    lv_timer_handler();
    usleep(SLEEP_TIME_uSEC);
  }

  return 0;
}
