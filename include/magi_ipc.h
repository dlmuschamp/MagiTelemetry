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

// The internal logging logic
static inline void _magi_logger(const char *subsystem, const char *message,
                                int original_errno) {
  time_t now = time(NULL);
  struct tm *tinfo = localtime(&now);
  char date_buffer[32];

  // Formats the time into a clean string: YYYY-MM-DD HH:MM:SS
  strftime(date_buffer, sizeof(date_buffer), "%Y-%m-%d %H:%M:%S", tinfo);

  // Print both timestamps, the subsystem, the custom message, and the kernel
  // error
  fprintf(stderr, "[%ld] [%s] [MAGI CRITICAL] [%s] %s: %s\n", (long)now,
          date_buffer, subsystem, message, strerror(original_errno));
}

// Custom error logging format
#define MAGI_LOG_ERROR(subsystem, message)                                     \
  _magi_logger(subsystem, message, errno)

#endif
