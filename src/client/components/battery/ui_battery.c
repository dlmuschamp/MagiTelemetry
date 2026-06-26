#include "ui_battery.h"
#include "ui_styles.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

// Restored Original Constants
static const unsigned int SEC_PER_HR = 3600, SEC_PER_MIN = 60, MIN_PER_HR = 60;
static const unsigned long NANO_TO_CENTI_SEC = 10000000, CENTI_COUNTDOWN = 99;
static const char *BAT_SUBSYS = "BATTERY";

// Construction logic: Creates the battery UI element
lv_obj_t *create_battery_label(lv_obj_t *parent) {
  lv_obj_t *label = lv_label_create(parent);
  lv_obj_center(label);
  return label;
}

// Logic: Initializes the telemetry data context
ui_context_t *init_battery_context(lv_obj_t *label) {
  ui_context_t *ctx = malloc(sizeof(ui_context_t));
  if (ctx == NULL)
    return NULL;

  int shm_fd = shm_open(SHM_BATTERY, O_RDONLY, UNIX_RDWR_PERM);
  ctx->battery_daemon_info = MAP_FAILED;

  if (shm_fd != -1) {
    ctx->battery_daemon_info =
        mmap(0, sizeof(magi_battery_data_t), PROT_READ, MAP_SHARED, shm_fd, 0);
  } else {
    MAGI_LOG_ERROR(BAT_SUBSYS, "Failed to open shared memory!");
  }

  ctx->main_label = label;
  ctx->current_frame_index = 0;
  ctx->current_ui_sec = 0;

  lv_timer_create(render_battery, FPS_REFRESH_MS, ctx);

  return ctx;
}

// Rendering callback: Updates the UI every frame with exact original math
void render_battery(lv_timer_t *timer) {
  ui_context_t *ui_ctx = (ui_context_t *)lv_timer_get_user_data(timer);
  if (ui_ctx == NULL)
    return;

  // lazy way to get around the fps thing
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

  // Exact original math restored
  int hrs = ui_ctx->current_ui_sec / SEC_PER_HR;
  int min = (ui_ctx->current_ui_sec % SEC_PER_HR) / SEC_PER_MIN;
  int sec = ui_ctx->current_ui_sec % SEC_PER_MIN;

  // lazy centisecs trick restored
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  int centi_sec = ts.tv_nsec / NANO_TO_CENTI_SEC;
  int disp_centi_sec = CENTI_COUNTDOWN - centi_sec;

  // Render
  lv_label_set_text_fmt(ui_ctx->main_label,
                        "ACTIVE TIME REMAINING:\n%1d:%02d:%02d:%02d", hrs, min,
                        sec, disp_centi_sec);
}
