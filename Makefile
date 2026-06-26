CC = gcc
CFLAGS_CLIENT = -g -O3 -std=gnu99 -I./include -I./src/client -I./src/client/lvgl
LDFLAGS_CLIENT = -lrt -lwayland-client -lwayland-cursor -lxkbcommon

# --- SOURCES ---
# Client
CLIENT_SRCS := $(shell find src/client -type f -name "*.c" ! -path "*/lvgl/*")
LVGL_SRCS := $(shell find src/client/lvgl/src -type f -name "*.c" ! -path "*/tests/*")
SRCS := $(CLIENT_SRCS) $(LVGL_SRCS)
OBJS := $(SRCS:%.c=bin/%.o)

# Daemon
DAEMON_SRC := src/daemons/battery.c
DAEMON_BIN := bin/magi_battery_daemon

# --- RULES ---
# Build BOTH the client and the daemon
all: bin/magi_client $(DAEMON_BIN)

# 1. Compile the Daemon
$(DAEMON_BIN): $(DAEMON_SRC)
	@mkdir -p bin
	@echo "Compiling Daemon..."
	$(CC) -g -O3 -std=gnu99 -I./include $< -o $@ -lrt

# 2. Compile the Client Objects
bin/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS_CLIENT) -c $< -o $@

# 3. Link the Client
bin/magi_client: $(OBJS)
	@echo "Linking Client..."
	$(CC) $(OBJS) -o $@ $(LDFLAGS_CLIENT)

clean:
	rm -rf bin/

.PHONY: all clean
