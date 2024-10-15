CC := gcc
CFLAGS := -Werror -Wall

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS: src/%.c=bin/%.o)
TRGT := bin/wish

all: $(TRGT)

$(TRGT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) bin/*
