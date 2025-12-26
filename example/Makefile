TARGET = main
CC = gcc
CFLAGS = -I../include
# LDFLAGS tells the linker where to find the .so at compile time
# -Wl,-rpath tells the loader where to find the .so at runtime
LDFLAGS = -L../ -lallocator -Wl,-rpath='$$ORIGIN/../'

all: $(TARGET)

# Added main.c as a dependency so it recompiles when the file changes
$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(CFLAGS) $(LDFLAGS)

.PHONY: all clean

clean:
	rm -f $(TARGET)