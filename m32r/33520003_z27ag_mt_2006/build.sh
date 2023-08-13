#!/bin/sh

m32r-elf-gcc -nostdlib -I./ -I./zag -Os -c \
	-DCLUTCH_INPUT_INVERTED \
	-DSMALL_DATA_AREA_BASE=0x808000 \
	-DNLTS_MODULE_ENABLED \
	-DTEMP_AXIS_SRC_SDA=-13008 \
	-DTEMP_AXIS_TARGET_X_SDA=-13002 \
	-DTEMP_AXIS_TARGET_Y_SDA=-13000 \
	-DMAP_ENGINE_LOAD_POINTER=-12656 \
	-I../../include \
	-I../../include/m32r \
	-I../../include/mods \
	-I./ \
	-Os -c \
	-fno-leading-underscore \
	-ffixed-r13			\
	../../src/map_base.c \
	../../src/colt_mt_cvt_dash_control.c \
	../../src/colt_mt_cvt_dash_control_data.c \
	../../src/knock_mil_simple.c		\
	../../src/knock_mil_data.c		\
	../../src/gpio_outputs_hijack.c \
	../../src/revolution_limit.c \
	../../src/revolution_limit_data.c	\
	../../src/nlts/nlts_simple.c		\
	../../src/nlts/nlts_data_simple.c	\
	../../src/load_extender.c		\
	../../src/obd.c				\
	../../src/obd_data.c			\
	../../src/load400_math.c


m32r-elf-ld -T omni.ld -o omni.elf	\
	map_base.o			\
	knock_mil_simple.o		\
	knock_mil_data.o		\
	load_extender.o			\
	obd.o				\
	obd_data.o			\
	load400_math.o			\
	gpio_outputs_hijack.o		\
	revolution_limit.o		\
	revolution_limit_data.o		\
	colt_mt_cvt_dash_control.o	\
	colt_mt_cvt_dash_control_data.o	\
	nlts_simple.o			\
	nlts_data_simple.o

../../tools/codeinjector/codeinjector mmc-m32r Z27AG_JDM_5MT_1860B104.bin omni.elf colt_patched_3352a203.bin > 3352a203_patch.xml
