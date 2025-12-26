CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -g -fPIC -I./include
LDFLAGS = -shared

SRC_DIR   	= ./src
BUILD_DIR 	= ./build
WRAPPER_DIR = ./wrapper

TARGET 			= liballocator.so
WRAPPER_TARGET	= libwrapper.so

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

WRAPPER_SRC = $(WRAPPER_DIR)/wrapper.c
WRAPPER_OBJ = $(BUILD_DIR)/wrapper.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Successfully built library: $(TARGET)"

wrapper: $(OBJS) $(WRAPPER_OBJ)
	$(CC) $(LDFLAGS) -o $(WRAPPER_TARGET) $^
	@echo "Successfully built wrapper: $(WRAPPER_TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(WRAPPER_OBJ): $(WRAPPER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean