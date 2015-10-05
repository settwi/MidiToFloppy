# To set UFLAGS, here is the format:
# $ UFLAGS="-g -DWrandom-warning" make midi

CFLAGS =-std=c99 -Wall -Wextra -pedantic
NAME ?= mtof

OBJS = $(patsubst %.c,%.o,$(wildcard src/*.c))

.PHONY: midi clean cleana

all: $(OBJS) midi 
	
midi: $(OBJS)
	cc $(CFLAGS) $(UFLAGS) -o $(NAME) $(OBJS)

cleana:
	rm -f $(NAME) music/**/*.mid.* $(OBJS)

clean:
	rm -f music/**/*.mid.*
