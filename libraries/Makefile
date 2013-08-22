
SRC = \
			malloc.c

OBJS = $(SRC:.c=.o)

all: shared

%.o: %.c
	gcc -fpic -g -c -Wall $< -ldl

shared:: $(OBJS)
	gcc -shared -Wl,-soname,$(subst .o,.so,$<) -o $(subst .o,.so,$<) $< -ldl

clean:
	-rm *.o *.so

.PHONY: clean

