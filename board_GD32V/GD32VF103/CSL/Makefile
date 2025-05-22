
C_SRCS = \
	$(CSL_DIR)/RISCV/core/n200_func.c \
	$(CSL_DIR)/RISCV/stubs/sbrk.c \
	$(CSL_DIR)/RISCV/startup/handlers.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/system_gd32vf103.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_gpio.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_rcu.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_timer.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_eclic.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_exti.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_pmu.c \
	$(CSL_DIR)/GD32VF103_standard_peripheral/Source/gd32vf103_usart.c \

C_INCS = \
	-I$(CSL_DIR) \
	-I$(CSL_DIR)/RISCV/core \
	-I$(CSL_DIR)/GD32VF103_standard_peripheral \
	-I$(CSL_DIR)/GD32VF103_standard_peripheral/Include \

C_DEFS = \
	-DUSE_STDPERIPH_DRIVER \
	-DGD32VF103C_START

S_SRCS = \
	$(CSL_DIR)/RISCV/startup/entry.S \
	$(CSL_DIR)/RISCV/startup/start.S

S_INCS = 

S_DEFS = 

LIBS = -nostartfiles
LIBDIR = 

MACHINE = -march=rv32imac_zicsr_zifencei -mabi=ilp32 -msmall-data-limit=8
CFLAGS = $(MACHINE)
SFLAGS = $(MACHINE)

LDSCRIPT = $(CSL_DIR)/RISCV/startup/GD32VF103xB.lds
LDFLAGS  = $(MACHINE) -specs=nano.specs -T$(LDSCRIPT)
