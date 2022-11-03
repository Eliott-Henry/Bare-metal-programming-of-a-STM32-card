PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
GDB = $(PREFIX)gdb
LD = $(PREFIX)ld
AS = $(PREFIX)as

CFLAGS = -ffreestanding -Wall -Wextra -Werror  -g -O1 # -c 
LDFLAGS = -nostdlib -T ld_ram.lds
CPPFLAGS = -ICMSIS/Include -ICMSIS/Device/ST/STM32L4xx/Include -DSTM32L475xx

TARGET_ARCH = -mcpu=cortex-m4 -mthumb # We can add -mfloat-abi=hard -mpfu=fpv4-sp-d16 (pour compile.c)
TARGET_ARCH += -mfloat-abi=hard -mfpu=fpv4-sp-d16# pour débuger l'édition de lien avec clocks.o

ASFLAGS = -g
TARGET_MACH = $(TARGET_ARCH)


EXE = prog
OBJS = main.o crt0.o init.o memfuncs.o led.o uart.o matrix.o irq.o buttons.o

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -g $(LDFLAGS)  $^ clocks.o -o $@

# Pour se connecter
connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

run: $(EXE)
	$(GDB) -x ses203.gdb $<

uart: hello
	$(GDB) -x ses203.gdb $<

objdump:
	arm-none-eabi-objdump -h $(EXE)

tio:
	tio /dev/ttyACM0

clean:
	rm -f $(OBJS)
	rm -f $(EXE)