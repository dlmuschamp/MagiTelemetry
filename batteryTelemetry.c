/**
 * @file
 * @brief batteryTelemetry is a program that
 * simply reads and prints out the remaining
 * battery of my laptop in pure C as part of
 * my larger NGE-inspired hardware info daemon
 * project. This is my first C project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //unix standard

#define BAT_PERCENT_PATH "/sys/class/power_supply/BAT0/capacity"
#define BAT_ENERGY_PATH "/sys/class/power_supply/BAT0/energy_now"
#define BAT_POWER_PATH "/sys/class/power_supply/BAT0/power_now"

#define BUFFER_SIZE 64
#define BASE 10

long get_hardware_value(const char path[]);

int main() {
  long cur_bat = get_hardware_value(BAT_PERCENT_PATH);
  long cur_energy = get_hardware_value(BAT_ENERGY_PATH);
  long cur_power = get_hardware_value(BAT_POWER_PATH);

  printf("Current Battery Percent: %ld\nCurrent Battery Energy: %ld\nCurrent "
         "Battery Power: %ld\n",
         cur_bat, cur_energy, cur_power);
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
