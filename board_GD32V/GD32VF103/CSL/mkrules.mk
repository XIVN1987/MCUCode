
PREFIX = riscv-none-elf-

CC   = $(PREFIX)gcc
AS   = $(PREFIX)gcc -x assembler-with-cpp
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump


###############################################################################
#

CFLAGS += $(OPT) $(C_DEFS) $(C_INCS)
CFLAGS += -fdata-sections -ffunction-sections -MMD -MF"$(@:%.o=%.d)"

SFLAGS += $(OPT) $(C_DEFS) $(C_INCS) $(S_DEFS) $(S_INCS)
SFLAGS += -fdata-sections -ffunction-sections -MMD -MF"$(@:%.o=%.d)"

ifdef LD_NO_GC
LDFLAGS+= $(OPT) $(LIBS) $(LIBDIR) -T$(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(EXE).map,--cref
else
LDFLAGS+= $(OPT) $(LIBS) $(LIBDIR) -T$(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(EXE).map,--cref -Wl,--gc-sections
endif


OBJS = $(addprefix $(BUILD_DIR)/,$(C_SRCS:.c=.o) $(S_SRCS:.S=.o))
DEPS = $(addprefix $(BUILD_DIR)/,$(C_SRCS:.c=.d) $(S_SRCS:.S=.d))


###############################################################################
#

all: $(BUILD_DIR)/$(EXE).bin $(BUILD_DIR)/$(EXE).dis

vpath %.c . $(dir $(CSL_DIR))
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

vpath %.S . $(dir $(CSL_DIR))
$(BUILD_DIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(AS) -c $(SFLAGS) $< -o $@

$(BUILD_DIR)/$(EXE).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(COPY) -O binary -S $< $@

$(BUILD_DIR)/%.dis: $(BUILD_DIR)/%.elf
	$(DUMP) -d $< > $@

clean:
	rm -rf $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(DEPS)