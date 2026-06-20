#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>  // So I can use printf() to debug
#include <stdlib.h> // Standard types
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h> // For usleep()

#include "lv_conf.h"
#include "lvgl/lvgl.h"
#include "magi_ipc.h" // My custom logging macro

static const uint32_t HOR_RES = 400, VER_RES = 300;
static const uint32_t RENDER_FPS = 24;
static const uint32_t FPS_REFRESH_MS = 1000 / RENDER_FPS;
static const unsigned int SLEEP_TIME_uSEC = 5000;
static const unsigned int SEC_PER_HR = 3600, SEC_PER_MIN = 60, MIN_PER_HR = 60;
static const unsigned long NANO_TO_CENTI_SEC = 10000000, CENTI_COUNTDOWN = 99;

// find out pros and cons of unsigned ints.
static char *WINDOW_NAME = "Magi Display";
static const char *MAIN_SUBSYS = "MAIN";

// (Assuming MAX_DEVIATION_SEC is defined here or in magi_ipc.h)
#ifndef MAX_DEVIATION_SEC
#define MAX_DEVIATION_SEC 600
#endif

// Render Context Struct
typedef struct {
  magi_battery_data_t *battery_daemon_info; // Pointer to shared memory struct
  lv_obj_t *main_label;
  int current_ui_sec;
  int current_frame_index;
} ui_context_t;

// Function signatures
void render(lv_timer_t *timer);

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

  // CLIENT SIDE IPC: We only want to READ the memory the daemon created
  int shm_fd = shm_open(SHM_BATTERY, O_RDONLY, 0666);
  magi_battery_data_t *batd_info = MAP_FAILED;

  if (shm_fd != -1) {
    batd_info =
        mmap(0, sizeof(magi_battery_data_t), PROT_READ, MAP_SHARED, shm_fd, 0);
  }

  ui_context_t *ctx = malloc(sizeof(ui_context_t));
  ctx->battery_daemon_info = batd_info;
  ctx->main_label = label;
  ctx->current_frame_index = 0;
  ctx->current_ui_sec = 0;

  lv_timer_create(render, FPS_REFRESH_MS, ctx);
  while (1) {
    lv_timer_handler();
    usleep(SLEEP_TIME_uSEC);
  }

  return 0;
}

/**
 * @brief
 *
 * @param timer [TODO:parameter]
 */
void render(lv_timer_t *timer) {
  ui_context_t *ui_ctx = lv_timer_get_user_data(timer);

  // lazy way to get around the fps thing but basically count which frame we are
  // on and only decrease after the number of frames in a single second
  // and use mod. i didnt want to use time yet
  if (ui_ctx->current_frame_index == 0 && ui_ctx->current_ui_sec > 0) {
    ui_ctx->current_ui_sec--;
  }
  ui_ctx->current_frame_index = (ui_ctx->current_frame_index + 1) % RENDER_FPS;

  // Ensure daemon is mapped before trying to read it
  if (ui_ctx->battery_daemon_info != MAP_FAILED) {
    if (labs(ui_ctx->current_ui_sec -
             ui_ctx->battery_daemon_info->shared_bat_sec) >=
        MAX_DEVIATION_SEC) {
      ui_ctx->current_ui_sec = ui_ctx->battery_daemon_info->shared_bat_sec;
    }
  }

  int hrs = ui_ctx->current_ui_sec / SEC_PER_HR;
  int min = (ui_ctx->current_ui_sec % SEC_PER_HR) / SEC_PER_MIN;
  int sec = ui_ctx->current_ui_sec % SEC_PER_MIN;

  // lazy centisecs trick
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  int centi_sec = ts.tv_nsec / NANO_TO_CENTI_SEC;
  int disp_centi_sec = CENTI_COUNTDOWN - centi_sec;

  // Render
  lv_label_set_text_fmt(ui_ctx->main_label,
                        "TIME REMAINING:\n%02d:%02d:%02d:%02d", hrs, min, sec,
                        disp_centi_sec);
}
