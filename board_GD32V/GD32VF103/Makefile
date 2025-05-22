BUILD_DIR = build

TARGET = GD32VF103


CSL_DIR = CSL
include $(CSL_DIR)/Makefile


C_SRCS += \
	main.c \

C_INCS += \
	-I. \


###############################################################################
#
PREFIX = riscv-none-elf-

CC   = $(PREFIX)gcc
AS   = $(PREFIX)gcc -x assembler-with-cpp
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump

OPT = -Og

CFLAGS += -g $(OPT) $(C_DEFS) $(C_INCS)
CFLAGS += -fdata-sections -ffunction-sections -MMD -MF"$(@:%.o=%.d)"

SFLAGS += -g $(OPT) $(C_DEFS) $(C_INCS) $(S_DEFS) $(S_INCS)
SFLAGS += -fdata-sections -ffunction-sections -MMD -MF"$(@:%.o=%.d)"

LDFLAGS+= -g $(OPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


###############################################################################
#

all: $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).dis


# list of objects
OBJS = $(addprefix $(BUILD_DIR)/,$(C_SRCS:.c=.o))
DEPS = $(addprefix $(BUILD_DIR)/,$(C_SRCS:.c=.d))

# list of asm objects
OBJS+= $(addprefix $(BUILD_DIR)/,$(S_SRCS:.S=.o))
DEPS+= $(addprefix $(BUILD_DIR)/,$(S_SRCS:.S=.d))


$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(AS) -c $(SFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
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
