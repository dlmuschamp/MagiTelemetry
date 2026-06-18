# 1. Define the compiler
CC = gcc

# 2. The exact, CS107 flags + the include directory path
CFLAGS = -g -O0 -std=gnu99 -Wall -Wfloat-equal -Wtype-limits -Wpointer-arith -Wlogical-op -Wshadow -fno-diagnostics-show-option -I./include

# 3. Linker flags (POSIX Real-Time library for shared memory)
LDFLAGS_DAEMON = -lrt

# 4. The default rule: build everything
all: prep battery wifi cpu client

# 5. Create the bin/ directory silently if it doesn't exist
prep:
	@mkdir -p bin

# 6. Daemon Targets
# $< means "the input file" (e.g., src/daemons/battery.c)
battery: src/daemons/battery.c
	$(CC) $(CFLAGS) $< -o bin/magid_battery $(LDFLAGS_DAEMON)

wifi: src/daemons/wifi.c
	$(CC) $(CFLAGS) $< -o bin/magid_wifi $(LDFLAGS_DAEMON)

cpu: src/daemons/cpu.c
	$(CC) $(CFLAGS) $< -o bin/magid_cpu $(LDFLAGS_DAEMON)

# 7. Client Target (We will expand this later to include LVGL and SDL2)
client: src/client/main.c
	$(CC) $(CFLAGS) $< -o bin/magi_client $(LDFLAGS_DAEMON)

# 8. Clean up all generated executables
clean:
	rm -rf bin/

# Tell Make that these are commands, not actual files
.PHONY: all prep clean battery wifi cpu client
