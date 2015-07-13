CC      = gcc
CFLAGS  = -g
RM      = rm -f
LD      = gcc


default: all

all: emtest

emtest: emtest.o
	$(LD) -o emtest emtest.o

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) emtest emtest.o