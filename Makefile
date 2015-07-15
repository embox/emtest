CC      = gcc
CFLAGS  = -g
RM      = rm -f
LD      = gcc

OBJS = test1.o test2.o emtest.o

default: all

all: emtest

emtest: $(OBJS)
	$(LD) -T ./util/array_spread.lds -o emtest $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

%.o : tests/%.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) emtest $(OBJS)