#include "ui_battery.h"
#include "include/lvgl/api_map/lv_api_map_v8.h"
#include "include/lvgl/core/lv_obj.h"
#include "include/lvgl/core/lv_obj_pos.h"
#include "include/lvgl/core/lv_obj_style_gen.h"
#include "include/lvgl/draw/lv_color.h"
#include "include/lvgl/lv_types.h"
#include "include/lvgl/widgets/lv_label.h"
#include "magi_ipc.h"
#include "ui_styles.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

// Restored Original Constants
static const unsigned int SEC_PER_HR = 3600, SEC_PER_MIN = 60, MIN_PER_HR = 60;
static const unsigned long NANO_TO_CENTI_SEC = 10000000, CENTI_COUNTDOWN = 99;
static const char *BAT_SUBSYS = "BATTERY UI";
static const int NUM_BOX_WIDTH = 775, NUM_BOX_LENGTH = 300;
static const int BORDER_WIDTH = 1;
static const int SHADOW_WIDTH = 10;

lv_obj_t *create_battery_label(lv_obj_t *parent) {
  lv_obj_t *label = lv_label_create(parent);
  lv_obj_center(label);
  return label;
}

ui_context_t *init_battery_context(lv_obj_t *label) {
  ui_context_t *ctx = malloc(sizeof(ui_context_t));
  if (!ctx) {
    MAGI_LOG_ERROR(BAT_SUBSYS,
                   "Unable to allocate memory for battery UI context.");
    return NULL;
  }
  int shm_fd = shm_open(SHM_BATTERY, O_RDONLY, UNIX_RDWR_PERM);
  ctx->battery_daemon_info = MAP_FAILED;

  if (shm_fd != -1) {
    ctx->battery_daemon_info =
        mmap(0, sizeof(magi_battery_data_t), PROT_READ, MAP_SHARED, shm_fd, 0);
    close(shm_fd);
  } else {
    MAGI_LOG_ERROR(BAT_SUBSYS,
                   "Failed to open shared memory for battery daemon info");
  }

  ctx->main_label = label;
  ctx->current_frame_index = 0;
  ctx->current_ui_sec_elapsed = 0;

  lv_timer_create(render_battery_ui, FPS_REFRESH_MS, ctx);

  return ctx;
}

void setup_battery_ui(lv_obj_t *parent_screen) {

  if (!parent_screen) {
    MAGI_LOG_ERROR(BAT_SUBSYS, "Parent screen pointer is null.");
    return;
  }

  apply_bg_grad(parent_screen, BATTERY_START_GRAD_RED, BATTERY_END_GRAD_GREEN,
                LV_GRAD_DIR_HOR);

  lv_obj_t *num_box = lv_obj_create(parent_screen);
  lv_obj_clear_flag(num_box, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(num_box, NUM_BOX_WIDTH, NUM_BOX_LENGTH);
  lv_obj_center(num_box);
  lv_obj_set_style_bg_color(num_box, lv_color_hex(MAGI_COLOR_BLACK),
                            DEFAULT_STATE);

  // EVA-style border
  lv_obj_set_style_border_color(num_box, lv_color_hex(MAGI_COLOR_ORANGE),
                                DEFAULT_STATE);
  lv_obj_set_style_border_width(num_box, BORDER_WIDTH,
                                DEFAULT_STATE); // Increase weight
  lv_obj_set_style_border_side(num_box, LV_BORDER_SIDE_FULL, DEFAULT_STATE);

  // actual battery time label
  lv_obj_t *bat_label = create_battery_label(num_box);
  lv_obj_clear_flag(bat_label, LV_OBJ_FLAG_SCROLLABLE);

  apply_label_font_and_color(bat_label, &lv_font_7seg_175, MAGI_COLOR_ORANGE);
  lv_label_set_text(bat_label, "AWAITING DATA");

  ui_context_t *ctx = init_battery_context(bat_label);
}

void render_battery_ui(lv_timer_t *timer) {
  ui_context_t *ui_ctx = (ui_context_t *)lv_timer_get_user_data(timer);

  if (!ui_ctx) {
    MAGI_LOG_ERROR(BAT_SUBSYS, "UI Context pointer is null.");
    return;
  }

  // lazy way to get around the fps thing
  if (ui_ctx->current_frame_index == 0 && ui_ctx->current_ui_sec_elapsed > 0) {
    ui_ctx->current_ui_sec_elapsed--;
  }
  ui_ctx->current_frame_index = (ui_ctx->current_frame_index + 1) % RENDER_FPS;

  // Ensure daemon is mapped before trying to read it
  if (ui_ctx->battery_daemon_info != MAP_FAILED) {
    if (labs(ui_ctx->current_ui_sec_elapsed -
             ui_ctx->battery_daemon_info->shared_bat_sec) >=
        MAX_DEVIATION_SEC) {
      ui_ctx->current_ui_sec_elapsed =
          ui_ctx->battery_daemon_info->shared_bat_sec;
    }
  } else {
    MAGI_LOG_ERROR(
        BAT_SUBSYS,
        "Failed to map shared POSIX memory object for battery daemon info.");
  }

  // will never be negative
  int hrs = ui_ctx->current_ui_sec_elapsed / SEC_PER_HR;
  int min = (ui_ctx->current_ui_sec_elapsed % SEC_PER_HR) / SEC_PER_MIN;
  int sec = ui_ctx->current_ui_sec_elapsed % SEC_PER_MIN;

  // lazy centisecs trick restored
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  int centi_sec = ts.tv_nsec / NANO_TO_CENTI_SEC;
  int disp_centi_sec = CENTI_COUNTDOWN - centi_sec;

  // Render
  lv_label_set_text_fmt(ui_ctx->main_label, "%1d:%02d:%02d:%02d", hrs, min, sec,
                        disp_centi_sec); // active time remaining
}
