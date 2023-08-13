CC=m32r-elf-gcc
LD=m32r-elf-ld

DEFINES = -DARCH_M32R=1

CFLAGS = -nostdlib -I./ -I../../include -I../../include/m32r -I../../include/mods -Os -ffixed-r13 -fno-leading-underscore
LFLAGS = -T omni.ld

CODEINJECTOR=../../tools/codeinjector/codeinjector
