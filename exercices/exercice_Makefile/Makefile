PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
CFLAGS = -g -c
ERRORFLAGS = -Wall -Werror
TARGET_ARCH = -mthumb
LDLIBS = -L/opt/mylibs

EXE = hello
OBJS = main.o t1.o t2.o stubs.o

all: $(EXE) 

$(EXE) : $(OBJS)
	$(CC) $(LDLIBS) $(TARGET_ARCH) $^ -lm -o $@
#arm-none-eabi-gcc -L/opt/mylibs -mthumb main.o t1.o stubs.o t2.o -lm -o hello

stubs.o : libs/stubs.c
	$(CC) $(CFLAGS) -O2 $(TARGET_ARCH) -o $@ $^
#arm-none-eabi-gcc -g -O2 -mthumb -c -o stubs.o libs/stubs.c

%.o : %.c %.h
	$(CC) $(ERRORFLAGS) $(CFLAGS) -Og $(TARGET_ARCH) -o $@ $<
#arm-none-eabi-gcc -Wall -Werror -g -Og -mthumb -c -o t1.o t1.c
#arm-none-eabi-gcc -Wall -Werror -g -Og -mthumb -c -o t2.o t2.c

main.o: main.c t1.h t2.h
	$(CC) $(ERRORFLAGS) $(CFLAGS) -Og $(TARGET_ARCH) -o $@ $<
#arm-none-eabi-gcc -Wall -Werror -g -Og -mthumb -c -o main.o main.c

clean:
	rm -f *.o
	rm -f hello