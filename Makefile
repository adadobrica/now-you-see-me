CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGETS=NowYouSeeMe

build:	$(TARGETS)

NowYouSeeMe: struct.h utils.h
	$(CC) NowYouSeeMe.c -o NowYouSeeMe utils.c $(CFLAGS)

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
