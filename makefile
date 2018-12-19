CC=gcc
CFLAGS=-Wall -Werror
LIBS=-lpthread -lrt
HOST_= interfaceConn.h host.c
CONN_=$(shell find . -name "conn_*.c")
EXECUTABLES=$(CONN_:./conn_%.c=host_%)

all: $(EXECUTABLES)
	
host_%: conn_%.o $(HOST_:.c=.o)

	$(CC) -o $@ $^ $(LIBS) $(GRAPHLIB)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f `find . -maxdepth 1 -executable -type f`
