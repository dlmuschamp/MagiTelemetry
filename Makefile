CC = gcc
CFLAGS = -g -O3 -std=gnu99 -I./include -I./src/client -I./src/client/lvgl
LDFLAGS_CLIENT = -Lbin -llvgl -lrt -lwayland-client -lwayland-cursor -lxkbcommon

# Source Definitions
CLIENT_SRCS := $(shell find src/client -type f -name "*.c" ! -path "*/lvgl/*")
LVGL_SRCS   := $(shell find src/client/lvgl/src -type f -name "*.c" ! -path "*/tests/*")
DAEMON_SRC  := src/daemons/battery.c

# Object Definitions
CLIENT_OBJS := $(CLIENT_SRCS:%.c=bin/%.o)
LVGL_OBJS   := $(LVGL_SRCS:%.c=bin/%.o)

all: bin/magi_client bin/magi_battery_daemon

# 1. Build the Daemon
bin/magi_battery_daemon: $(DAEMON_SRC)
	@mkdir -p bin
	@echo "Compiling Daemon..."
	$(CC) -g -O3 -std=gnu99 -I./include $< -o $@ -lrt

# 2. Build LVGL as a Static Library
bin/liblvgl.a: $(LVGL_OBJS)
	@ar rcs $@ $^

# 3. Compile Client Objects
bin/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Link Client against the Static Library
bin/magi_client: $(CLIENT_OBJS) bin/liblvgl.a
	@echo "Linking Client..."
	$(CC) $(CLIENT_OBJS) -o $@ $(LDFLAGS_CLIENT)

clean:
	rm -rf bin/

.PHONY: all clean
