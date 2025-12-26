TARGET = main
CC = gcc
CFLAGS = -I../include
LDFLAGS = -L../ -lallocator -Wl,-rpath='$$ORIGIN/../'

all: $(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(CFLAGS) $(LDFLAGS)

.PHONY: all clean

clean:
	rm -f $(TARGET)
