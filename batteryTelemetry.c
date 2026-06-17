/**
 * @file
 * @brief batteryTelemetry is a program that
 * simply reads and prints out the remaining
 * battery of my laptop in pure C as part of
 * my larger NGE-inspired hardware info daemon
 * project. This is my first C project.
 */

#include <fcntl.h> // "File Control". Provides the O_CREAT and O_RDWR flags to tell Linux HOW to open the shared memory.
#include <stdio.h>
#include <stdlib.h> // Provides labs() for absolute values, and strtol() for parsing kernel strings.
#include <sys/mman.h> // "Memory Management". Provides the core IPC functions: shm_open() and mmap().
#include <sys/stat.h> // Provides file mode constants (like the 0666 permissions) used when creating shared memory.
#include <time.h> // Provides time(NULL) to get the current Unix timestamp for the shadow simulation.
#include <unistd.h> // "Unix Standard". Provides sleep(), ftruncate() to size memory, and close().

#define BAT_ENERGY_PATH "/sys/class/power_supply/BAT0/energy_now"
#define BAT_POWER_PATH "/sys/class/power_supply/BAT0/power_now"

#define BUFFER_SIZE 64
#define BASE 10
#define POWER_BUFFER_SIZE 10

#define SLEEP_TIMER 5

// Function Signatures
long get_hardware_value(const char path[]);

int main() {
  long rolling_power_values[POWER_BUFFER_SIZE] = {0};
  long power_avg = 0, total_battery_seconds = 0, remaining_battery_sec = 0,
       remaining_battery_min = 0, remaining_battery_hours = 0;
  int current_power_index = 0, num_readings = 0;

  printf("Waiting until a baseline power draw has been set...\n");

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

      // then compute total battery sec
      long cur_energy = get_hardware_value(BAT_ENERGY_PATH);
      total_battery_seconds =
          (cur_energy * 3600) / power_avg; // 3600 is num sec in 1 hr

      // lastly convert into hour, min, sec
      remaining_battery_hours = total_battery_seconds / 3600;
      remaining_battery_min = (total_battery_seconds % 3600) / 60;
      remaining_battery_sec = total_battery_seconds % 60;

      // print
      printf("Remaining battery: %02ld:%02ld:%02ld\n", remaining_battery_hours,
             remaining_battery_min, remaining_battery_sec);
    }

    sleep(SLEEP_TIMER);
  }

  // Successful Exit
  return 0;
}

/**
 * @brief Opens the specified kernel file, safely extracts the string data,
 * and converts it into a long integer.
 * * @param path The absolute system path to the target file
 * @return long The extracted integer, or -1 if the file fails to open
 */
long get_hardware_value(const char path[]) {
  FILE *sys_file = fopen(path, "r");

  if (sys_file == NULL) {
    printf("Could not locate a file at the specified path.\n");
    return -1;
  }

  char data_buffer[BUFFER_SIZE];
  fgets(data_buffer, BUFFER_SIZE, sys_file);
  long parsed_data = strtol(data_buffer, NULL, BASE);

  fclose(sys_file);
  return parsed_data;
}
