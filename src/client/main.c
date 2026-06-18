#include "magi_ipc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define UNIX_RDWR_PERM 0666

static const char *CLIENT_SUBSYS = "CLIENT";

// TESTING NOT THE FULL CLIENT
int main() {
  printf("MAGI Client Dummy: Booting up...\n");

  // 1. Open the shared memory block (Read Only)
  int shm_fd = shm_open(SHM_BATTERY, O_RDONLY, UNIX_RDWR_PERM);
  if (shm_fd == -1) {
    MAGI_LOG_ERROR(CLIENT_SUBSYS, "Could not locate /dev/shm/magi_battery");
    return 1;
  }

  // 2. Map the memory into this program (Read Only)
  long *shared_battery_sec =
      mmap(0, sizeof(long), PROT_READ, MAP_SHARED, shm_fd, 0);
  if (shared_battery_sec == MAP_FAILED) {
    MAGI_LOG_ERROR(CLIENT_SUBSYS, "Could not map memory");
    return 1;
  }

  printf("MAGI Link Established. Reading telemetry...\n");

  // 3. The Monitoring Loop
  while (1) {
    // We just read the pointer like a normal variable!
    long current_val = *shared_battery_sec;

    printf("Current Battery Dead Reckoning: %ld seconds\n", current_val);

    // Sleep for 2 seconds before checking again
    sleep(2);
  }

  return 0;
}
