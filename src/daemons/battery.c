/**
 * @file
 * @brief batteryTelemetry is a program that
 * simply reads and prints out the remaining
 * battery of my laptop in pure C as part of
 * my larger NGE-inspired hardware info daemon
 * project. This is my first C project.
 */

// include statements
#include "magi_ipc.h"
#include <fcntl.h> // "File Control". Provides the O_CREAT and O_RDWR flags to tell Linux HOW to open the shared memory.
#include <stdio.h>
#include <stdlib.h> // Provides labs() for absolute values, and strtol() for parsing kernel strings.
#include <sys/mman.h> // "Memory Management". Provides the core IPC functions: shm_open() and mmap().
#include <sys/stat.h> // Provides file mode constants (like the 0666 permissions) used when creating shared memory.
#include <time.h> // Provides time(NULL) to get the current Unix timestamp for the shadow simulation.
#include <unistd.h> // "Unix Standard". Provides sleep(), ftruncate() to size memory, and close().

// Buffer sizes needed at compile time so use #define
#define BUFFER_SIZE 64
#define POWER_BUFFER_SIZE 10
#define UNIX_RDWR_PERM 0666

// Use const for all other globals. Also use static to  ensure its only visible
// within this file
static const char *BAT_ENERGY_PATH = "/sys/class/power_supply/BAT0/energy_now";
static const char *BAT_POWER_PATH = "/sys/class/power_supply/BAT0/power_now";

static const int BASE = 10;
static const int SAMPLE_INTERVAL_SEC = 5;
static const int SEC_IN_HOUR = 3600;
static const int SEC_IN_10_MIN = 600;

static char *BAT_SUBSYS = "BATTERY";

// Function Signatures
static long get_hardware_value(const char *path);
static void battery_life_dead_reckoning(long total_battery_sec,
                                        long *shared_battery_sec,
                                        long *last_sent_battery_sec,
                                        long *last_sent_timestamp);

int main() {
  // shared memory set up
  int shm_fd = shm_open(SHM_BATTERY, O_CREAT | O_RDWR, UNIX_RDWR_PERM);
  if (shm_fd == -1) {
    MAGI_LOG_ERROR(BAT_SUBSYS, "Could not open shared memory.\n");
    return 1;
  }

  ftruncate(shm_fd, sizeof(long));

  long *shared_battery_sec =
      mmap(0, sizeof(long), PROT_WRITE, MAP_SHARED, shm_fd,
           0); // first 0 just tells kernel to find any spot in memory with
               // enough space, the second 0 says to start mapping the data from
               // byte 0 in the shared memory spot
  if (shared_battery_sec == MAP_FAILED) {
    MAGI_LOG_ERROR(BAT_SUBSYS, "Could not map shared memory.\n");
    return 1;
  }

  long rolling_power_values[POWER_BUFFER_SIZE] = {0};
  long power_avg = 0, total_battery_sec = 0;
  int current_power_index = 0, num_readings = 0;

  long last_sent_battery_seconds = -1, last_sent_timestamp = -1;

  // polling loop
  while (1) {
    rolling_power_values[current_power_index] =
        get_hardware_value(BAT_POWER_PATH);
    current_power_index = (current_power_index + 1) % POWER_BUFFER_SIZE;

    if (num_readings < POWER_BUFFER_SIZE) { // prevent overflow
      num_readings++;
    }

    if (num_readings >=
        POWER_BUFFER_SIZE) { // wait till we have the first 10 samples
      // first recalc power_avg
      long power_sum = 0;
      for (int i = 0; i < POWER_BUFFER_SIZE; i++) {
        power_sum += rolling_power_values[i];
      }
      power_avg = (double)power_sum / POWER_BUFFER_SIZE;

      // if laptop is charging, power_avg will be negative/0
      long cur_energy = get_hardware_value(BAT_ENERGY_PATH);
      if (power_avg <= 0) {
        total_battery_sec = -1;
      } else { // then compute total battery sec
        total_battery_sec = (cur_energy * SEC_IN_HOUR) / power_avg;
      }

      // call dead reckoning helper function
      battery_life_dead_reckoning(total_battery_sec, shared_battery_sec,
                                  &last_sent_battery_seconds,
                                  &last_sent_timestamp);
    }

    sleep(SAMPLE_INTERVAL_SEC);
  }

  return 0;
}

/**
 * @brief Opens the specified kernel file, safely extracts the string data,
 * and converts it into a long integer.
 * @param path The absolute system path to the target file
 * @return long The extracted integer, or -1 if the file fails to open
 */
static long get_hardware_value(const char *path) {
  FILE *sys_file = fopen(path, "r");

  if (sys_file == NULL) {
    MAGI_LOG_ERROR(BAT_SUBSYS,
                   "Could not locate a file at the specified path.\n");
    return -1;
  }

  char data_buffer[BUFFER_SIZE];
  fgets(data_buffer, BUFFER_SIZE, sys_file);
  long parsed_data = strtol(data_buffer, NULL, BASE);

  fclose(sys_file);
  return parsed_data;
}

/**
 * @brief Will only write new remaining battery life to shared memory if the
 * current calculated life deviates from the UI's simulated "dead reckoning"
 * approximation by 10 or more minutes (600 seconds).
 *
 * @param total_battery_sec The true battery calculated in main (passed by
 * value)
 * @param shared_battery_sec Pointer to the mapped POSIX memory block
 * @param last_sent_battery_sec Pointer to the anchor value stored in main
 * @param last_sent_timestamp Pointer to the anchor time stored in main
 */
static void battery_life_dead_reckoning(long total_battery_sec,
                                        long *shared_battery_sec,
                                        long *last_sent_battery_sec,
                                        long *last_sent_timestamp) {

  long cur_time = time(NULL);

  // First run. No anchor exists yet. Initialize and write to memory.
  if (*last_sent_battery_sec == -1) {
    *shared_battery_sec = total_battery_sec;
    *last_sent_battery_sec = total_battery_sec;
    *last_sent_timestamp = cur_time;
  } else {
    // check elapsed time to current estimate
    long seconds_since_last_update = cur_time - *last_sent_timestamp;
    long simulated_time_remaining_sec =
        *last_sent_battery_sec - seconds_since_last_update;

    if (simulated_time_remaining_sec <= 0) {
      simulated_time_remaining_sec = -1;
    }

    // drift check
    long drift_deviation =
        labs(total_battery_sec - simulated_time_remaining_sec);

    if (drift_deviation >= SEC_IN_10_MIN) {
      *shared_battery_sec = total_battery_sec;
      *last_sent_battery_sec = total_battery_sec;
      *last_sent_timestamp = cur_time;
    }
  }
}
