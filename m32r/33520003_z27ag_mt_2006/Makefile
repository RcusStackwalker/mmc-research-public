include ../toolchain.mk

DEFINES += -DMACHINE_Z27AGMT \
	-DCLUTCH_INPUT_INVERTED \
	-DNLTS_MODULE_ENABLED \
	-DTEMP_AXIS_SRC_SDA=-13008 \
	-DTEMP_AXIS_TARGET_X_SDA=-13002 \
	-DTEMP_AXIS_TARGET_Y_SDA=-13000 \
	-DMAP_ENGINE_LOAD_POINTER=-12656 \
	-DASC_TO_DASH_RX_SLOT_INDEX=12 \
	-DENGINE_TO_CVT_DASH_TX_SLOT_INDEX=15 \
	-DKNOCK_CEL_MODE_CHANGE_INDICATION \
	-DCAN_ETACS_RX_SLOT=5

#TODO: ADD BOOOST AND ACCELERATOR PEDAL CHARACTERISTICS


SOURCES = ../../src/gear_detector.c \
	../../src/gear_detector_data.c \
	precision_boost.c \
	../../src/map_base.c \
	../../src/map_base_data.c \
	../../src/start_ceremony.c \
	../../src/start_ceremony_data.c \
	../../src/colt_mt_cvt_dash_control.c \
	../../src/colt_mt_cvt_dash_control_data.c \
	../../src/asc_to_dash_rx.c \
	../../src/knock_mil_simple.c		\
	../../src/knock_mil_data.c		\
	../../src/gpio_outputs_hijack.c \
	../../src/revolution_limit.c \
	../../src/revolution_limit_data.c	\
	../../src/nlts/nlts_simple.c		\
	../../src/nlts/nlts_data_simple.c	\
	../../src/load_extender_alt.c		\
	../../src/injectors_alt.c		\
	../../src/boost_alt_data.c		\
	../../src/obd.c				\
	../../src/obd_data.c			\
	../../src/load400_math.c		\
	../../src/etacs_handler_extension.c	\
	../../src/mode_selector_v2_data.c	\
	../../src/mode_selector_v2.c

OBJECTS=$(SOURCES:.c=.o)

ORIGINAL_FILE=Z27AG_JDM_5MT_1860B104.bin
ELF_OUT_FILE=omni.elf
BIN_OUT_FILE=3352a403_patched.bin
XML_HEADER_FILE=3352a403_header.xml
XML_PATCH_FILE=3352a403_patches.xml
XML_OUT_FILE=3352a403.xml

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $< -c -o $@

all: $(SOURCES) $(ELF_OUT_FILE) $(BIN_OUT_FILE) $(XML_OUT_FILE)

$(ELF_OUT_FILE): $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS) -o $@

$(BIN_OUT_FILE): $(ELF_OUT_FILE)
	$(CODEINJECTOR) mmc-m32r $(ORIGINAL_FILE) $(ELF_OUT_FILE) $(BIN_OUT_FILE) > $(XML_PATCH_FILE)

$(XML_OUT_FILE): $(BIN_OUT_FILE)
	echo '<rom>' > $(XML_OUT_FILE)	&& \
	cat $(XML_HEADER_FILE) >>  $(XML_OUT_FILE) && \
	cat $(XML_PATCH_FILE) >>  $(XML_OUT_FILE) && \
	echo '</rom>' >>  $(XML_OUT_FILE)

clean:
	rm $(OBJECTS) $(ELF_OUT_FILE)
