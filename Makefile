# 1. Define the compiler
CC = gcc

# 2. The exact, ultra-strict CS107 flags from the course reader
CFLAGS = -g -O0 -std=gnu99 -Wall -Wfloat-equal -Wtype-limits -Wpointer-arith -Wlogical-op -Wshadow -fno-diagnostics-show-option

# 3. Automatically find all .c files in the current directory
SRCS = $(wildcard *.c)

# 4. Generate a list of target executables by stripping the ".c" extension
# (e.g., "battery.c telemetry.c" becomes "battery telemetry")
PROGS = $(patsubst %.c,%,$(SRCS))

# 5. The default rule: if you just type 'make', compile all found programs
all: $(PROGS)

# 6. The Pattern Rule: How to build ANY program from its .c file
# $< means "the input file" (e.g., battery.c)
# $@ means "the target name" (e.g., battery)
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# 7. Clean up all generated executables
clean:
	rm -f $(PROGS)

# Tell Make that 'all' and 'clean' aren't actual files we want to build
.PHONY: all clean
