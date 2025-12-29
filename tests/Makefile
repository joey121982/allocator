CC = gcc
CFLAGS = -I../include -O0 -ggdb3
LDFLAGS = -L../ -lallocator -Wl,-rpath='$$ORIGIN/../'

SRCS = $(wildcard *.c)

TARGETS = $(SRCS:.c=)

all: $(TARGETS)

$(TARGETS): %: %.c
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)

test: all
	@for exe in $(TARGETS); do \
		echo "--------------------------------------------"; \
		./$$exe; \
	done
	@echo "--------------------------------------------"
	@echo "All tests completed."

clean:
	rm -f $(TARGETS)
	
.PHONY: all clean test