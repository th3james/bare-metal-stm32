#!/usr/bin/env sh
# Generate the object file
arm-none-eabi-gcc -o main.o -c -g -mcpu=cortex-m4 -mthumb main.c -nostdlib
# Generate the executable file
arm-none-eabi-gcc -o application.elf -Wl,-Tmemory.ld -nostartfiles -nodefaultlibs main.o
# Generate the binary file
arm-none-eabi-objcopy -O binary application.elf application.bin
