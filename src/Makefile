src = $(wildcard *.c*)
obj = $(src:.c=.o)
CC = g++
CFLAGS = -Wall -DLOCAL_DBG

client-duh: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) duh.exe