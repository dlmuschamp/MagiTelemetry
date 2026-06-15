/**
* Damian Luciano Muschamp 
* 14 Jun 2026
* ------------------------
* batteryTelemetry is a program that 
* simply reads and prints out the remaining
* battery of my laptop in pure C as part of 
* my larger NGE-inspired hardware info daemon
* project. This is my first C project. 
*/

#include <stdio.h>
#include <stdlib.h>

//#define is a "preprocesser directive" so its basically direct text replacement
//during compilation. we use this for declaring arrays in C because array declaration 
//requires a specific numerical value to know how much space to allocate for that array.

#define BAT_PERCENT_PATH "/sys/class/power_supply/BAT0/capacity"
#define BAT_BUFFER_SIZE 10

int main() {

  FILE *bat_percent_info = fopen(BAT_PERCENT_PATH, "r");

  if (bat_percent_info == NULL) {
    printf("Could not locate a file at the specified path.\n");
    return 1;
  }

  //New char buffer (string) to store the battery percent info
  char perc_buffer[BAT_BUFFER_SIZE];

  //Reading the file and writing the characters to the buffer
  fgets(perc_buffer, BAT_BUFFER_SIZE, bat_percent_info);

  //Printing the final buffer. %s means to print the entire string (char buffer)
  printf("Current battery: %s", perc_buffer);

  fclose(bat_percent_info);

  //Successful Exit
  return 0; 
}
