#ifndef MAGI_IPC_H
#define MAGI_IPC_H

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Shared Memory Paths
#define SHM_BATTERY "/magi_battery"
#define SHM_WIFI "/magi_wifi"
#define SHM_CPU "/magi_cpu"
#define UNIX_RDWR_PERM 0666
#define MAX_DEVIATION_SEC                                                      \
  1200 // max time before updating timers to sync up
       // again

static const int DATE_BUFFER_SIZE = 32;
// Battery Daemon Struct
typedef struct {
  long bat_percent;
  long shared_bat_sec;
  long power_avg; // charging if negative

} magi_battery_data_t;

// The internal logging logic
static inline void _magi_logger(const char *subsystem, const char *message,
                                int original_errno) {
  time_t now = time(NULL);
  struct tm *tinfo = localtime(&now);
  char date_buffer[DATE_BUFFER_SIZE];

  // Formats the time into a clean string: YYYY-MM-DD HH:MM:SS
  strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d %H:%M:%S", tinfo);

  const char *sub = (subsystem) ? subsystem : "UNKNWON";
  const char *msg = (message) ? message : "No message";

  // Print both timestamps, the subsystem, the custom message, and the kernel
  // error
  if (original_errno != 0) {
    fprintf(stderr, "[%ld] [%s] [MAGI CRITICAL] [%s] %s: %s\n", (long)now,
            date_buffer, sub, msg, strerror(original_errno));
  } else {
    fprintf(stderr, "[%ld] [%s] [MAGI CRITICAL] [%s] %s\n", (long)now,
            date_buffer, sub, msg);
  }
}

// Custom error logging format
#define MAGI_LOG_ERROR(subsystem, message)                                     \
  _magi_logger(subsystem, message, errno)

#endif
