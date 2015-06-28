VPATH = src
OUT_PATH=./bin

CC=g++
# CFLAGS=-Wall -Wextra -Werror -I include
CFLAGS=-I include
LDFLAGS=-framework CoreServices

main: main.o clean_bin
	$(CC) $(CFLAGS) $< -o $(OUT_PATH)/$@ $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c $<

clean_bin:
	mkdir -p bin
	rm -rf bin/*
