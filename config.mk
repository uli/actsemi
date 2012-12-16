BASELIBC = ../../Baselibc
LIBACTSEMI = ../libactsemi

CC = mipsel-sde-elf-gcc
LD = $(CC)
AR = mipsel-sde-elf-ar

CFLAGS = -G0 -mno-gpopt -Wall -W -march=mips32r2
LDFLAGS = -G0 -nostartfiles -nostdlib -T actsemi.ld -Wl,-n
