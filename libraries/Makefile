
SRC = \
			bashpipe.c \
			malloc.c \
			sleep.c \
			exit.c

OBJS = $(SRC:.c=.o)
LIBS = $(SRC:.c=.so)

all: shared

shared:: $(LIBS)

test:: shared
	gcc -Wall test.c $(LIBS) -o test
	#LD_LIBRARY_PATH=. strace -f -ff -o logs/log ./test
	LD_LIBRARY_PATH=. ./test

%.so: %.o bashpipe.o
	gcc -shared -Wl,-soname,$(subst .o,.so,$<) -o $(subst .o,.so,$<) $< -ldl

%.o: %.c
	gcc -fpic -g -c -Wall $< -ldl

clean:
	-rm *.o *.so test

.PHONY: clean

