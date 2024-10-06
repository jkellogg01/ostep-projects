SRCS = main.c
TARG = wcat
CC   = gcc
OPTS = -Wall -O
# LIBS = n/a

OBJS = $(SRCS:.c=.o)

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)
