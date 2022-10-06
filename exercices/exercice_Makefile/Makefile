PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
CFLAGS = -Wall -Werror -g -Og 
CFLAGS_2 = -g -O2
TARGET_ARCH = -mthumb
LDFLAGS = -L/opt/mylibs

EXE = hello
OBJS = main.o t1.o t2.o stubs.o

all: $(EXE) 

$(EXE) : $(OBJS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ -lm -o $@
#arm-none-eabi-gcc -L/opt/mylibs -mthumb main.o t1.o stubs.o t2.o -lm -o hello

stubs.o : libs/stubs.c
	$(CC) $(CFLAGS_2) $(TARGET_ARCH) -c -o $@ $^
#arm-none-eabi-gcc -g -O2 -mthumb -c -o stubs.o libs/stubs.c

%.o : %.c %.h
	$(CC) $(CFLAGS) $(TARGET_ARCH) -c -o $@ $<
#arm-none-eabi-gcc -Wall -Werror -g -Og -mthumb -c -o t1.o t1.c
#arm-none-eabi-gcc -Wall -Werror -g -Og -mthumb -c -o t2.o t2.c

# Regle par defaut
#arm-none-eabi-gcc -Wall -Werror -g -Og -mthumb -c -o main.o main.c

clean:
	rm -f *.o
	rm -f hello