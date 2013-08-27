CFLAGS  = -D_GNU_SOURCE -Wall -std=gnu99 -Wextra -O2 -fpic -shared -ldl -fvisibility=hidden
LIBS = liblogresolve.so libstealcursor.so
CC = gcc

all: $(LIBS)

liblogresolve.so: logresolve.c liblogresolve.version
	$(CC) $(CFLAGS) -Wl,--version-script=liblogresolve.version -o $@ $<

libstealcursor.so: stealcursor.c
	$(CC) $(CFLAGS) -o $@ $<
