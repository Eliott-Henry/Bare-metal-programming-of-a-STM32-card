PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
GDB = $(PREFIX)gdb
LD = $(PREFIX)ld
AS = $(PREFIX)as

CFLAGS = -ffreestanding -Wall -Wextra -Werror  -g -O1 # -c 
LDFLAGS = -nostdlib -T ld_ram.lds
CPPFLAGS = -ICMSIS/Include -ICMSIS/Device/ST/STM32L4xx/Include 

TARGET_ARCH = -mcpu=cortex-m4 -mthumb # We can add -mfloat-abi=hard -mpfu=fpv4-sp-d16 (pour compile.c)
TARGET_ARCH += -mfloat-abi=hard -mfpu=fpv4-sp-d16# pour débuger l'édition de lien avec clocks.o

EXE = prog
OBJS = main.o crt0.o init.o memfuncs.o led.o

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS)  $^ clocks.o -o $@

# Pour se connecter
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

run: $(EXE)
	$(GDB) -x ses203.gdb $<

uart: hello
	$(GDB) -x ses203.gdb $<

objdump:
	arm-none-eabi-objdump -h $(EXE)

clean:
	rm -f $(OBJS)
	rm -f $(EXE)