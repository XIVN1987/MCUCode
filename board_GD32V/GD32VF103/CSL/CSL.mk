
C_SRCS = \
	CSL/RISCV/stubs/sbrk.c \
	CSL/RISCV/stubs/fstat.c \
	CSL/RISCV/stubs/isatty.c \
	CSL/RISCV/core/n200_func.c \
	CSL/RISCV/startup/handlers.c \
	CSL/GD32VF103_standard_peripheral/system_gd32vf103.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_rcu.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_adc.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_dac.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_dbg.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_dma.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_fmc.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_can.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_i2c.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_spi.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_gpio.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_exti.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_eclic.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_timer.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_usart.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_wwdgt.c \

C_INCS = \
	-I$(CSL_DIR) \
	-I$(CSL_DIR)/RISCV/core \
	-I$(CSL_DIR)/GD32VF103_standard_peripheral \
	-I$(CSL_DIR)/GD32VF103_standard_peripheral/Include \

C_DEFS = \
	-DUSE_STDPERIPH_DRIVER \
	-DGD32VF103C_START

S_SRCS = \
	CSL/RISCV/startup/entry.S \
	CSL/RISCV/startup/start.S

S_INCS = 

S_DEFS = 


MACHINE = -march=rv32imac_zicsr_zifencei -mabi=ilp32 -msmall-data-limit=8
CFLAGS  = $(MACHINE)
SFLAGS  = $(MACHINE)
LDFLAGS = $(MACHINE) -nostartfiles -specs=nano.specs
