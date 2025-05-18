BUILD_DIR = build

TARGET = GD32VF103


include CSL/Makefile


C_SRCS += \
	main.c \

C_INCS += \
	-I.


###############################################################################
#
PREFIX = riscv-none-elf-

CC   = $(PREFIX)gcc
AS   = $(PREFIX)gcc -x assembler-with-cpp
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump

OPT = -Og

CFLAGS += -Wall -fdata-sections -ffunction-sections -fshort-wchar
CFLAGS += -MMD -MF"$(@:%.o=%.d)"
CFLAGS += -fstack-usage
CFLAGS += -g $(OPT) $(C_DEFS) $(C_INCS)

SFLAGS += -Wall -fdata-sections -ffunction-sections
SFLAGS += -MMD -MF"$(@:%.o=%.d)" 
SFLAGS += -g $(OPT) $(C_DEFS) $(C_INCS) $(S_DEFS) $(S_INCS)

LDFLAGS+= -g $(OPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


###############################################################################
#

all: \
	$(BUILD_DIR)/$(TARGET).elf \
	$(BUILD_DIR)/$(TARGET).bin \
	$(BUILD_DIR)/$(TARGET).dis \

# list of objects
OBJS = $(addprefix $(BUILD_DIR)/,$(C_SRCS:.c=.o))
DEPS = $(addprefix $(BUILD_DIR)/,$(C_SRCS:.c=.d))

# list of asm objects
OBJS+= $(addprefix $(BUILD_DIR)/,$(S_SRCS:.S=.o))
DEPS+= $(addprefix $(BUILD_DIR)/,$(S_SRCS:.S=.d))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(<:.c=.lst) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(AS) -c $(SFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) Makefile CSL/Makefile | $(BUILD_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(COPY) -O binary -S $< $@

$(BUILD_DIR)/%.dis: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(DUMP) -d $< > $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(DEPS)
