BASELIBC = ../../Baselibc

CC = mipsel-sde-elf-gcc
LD = $(CC)
CFLAGS = -G0 -mno-gpopt -Wall -W -march=mips32r2
LDFLAGS = -G0 -nostartfiles -nostdlib -T actsemi.ld -Wl,-n
