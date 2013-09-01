CFLAGS  = -D_GNU_SOURCE -Wall -std=gnu99 -Wextra -O2 -fpic -shared -fvisibility=hidden
LIBS = liblogresolve.so libstealcursor.so librandom.so
CC = gcc

all: $(LIBS)

liblogresolve.so: logresolve.c liblogresolve.version
	$(CC) $(CFLAGS) -ldl -Wl,--version-script=liblogresolve.version -o $@ $<

librandom.so: random.c
	$(CC) $(CFLAGS) -o $@ $<

libstealcursor.so: stealcursor.c
	$(CC) $(CFLAGS) -ldl -o $@ $<
