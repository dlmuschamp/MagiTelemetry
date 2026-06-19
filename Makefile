CC = gcc

# 1. Strict, unoptimized flags for daemon code (perfect for debugging)
CFLAGS_DAEMON = -g -O0 -std=gnu99 -Wall -Wfloat-equal -Wtype-limits -Wpointer-arith -Wlogical-op -Wshadow -I./include

# 2. Fast, relaxed flags for the massive 3rd-party graphics engine
CFLAGS_CLIENT = -g -O3 -std=gnu99 -I./include -I./src/client

# 3. Linker flags
LDFLAGS_DAEMON = -lrt
LDFLAGS_CLIENT = -lrt -lwayland-client -lwayland-cursor -lxkbcommon

# 4. Bypass LVGL script
CSRCS := $(shell find src/client/lvgl/src -type f -name "*.c")

# 5. Default rule
all: prep battery wifi cpu client

prep:
	@mkdir -p bin

# 6. Daemon Targets
battery: src/daemons/battery.c
	@mkdir -p bin
	$(CC) $(CFLAGS_DAEMON) $< -o bin/magid_battery $(LDFLAGS_DAEMON)

wifi: src/daemons/wifi.c
	@mkdir -p bin
	$(CC) $(CFLAGS_DAEMON) $< -o bin/magid_wifi $(LDFLAGS_DAEMON)

cpu: src/daemons/cpu.c
	@mkdir -p bin
	$(CC) $(CFLAGS_DAEMON) $< -o bin/magid_cpu $(LDFLAGS_DAEMON)

# 7. Client Target (Uses the optimized CFLAGS_CLIENT)
client: src/client/main.c src/client/wayland_xdg_shell.c $(CSRCS)
	@mkdir -p bin
	$(CC) $(CFLAGS_CLIENT) $^ -o bin/magi_client $(LDFLAGS_CLIENT)

clean:
	rm -rf bin/

.PHONY: all prep clean battery wifi cpu client
