vpath %.c . $(dir $(CSL_DIR))
C_SRCS = \
	CSL/RISCV/stubs/sbrk.c \
	CSL/RISCV/stubs/fstat.c \
	CSL/RISCV/stubs/isatty.c \
	CSL/RISCV/startup/handlers.c \
	CSL/GD32VW55x_standard_peripheral/system_gd32vw55x.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_rcu.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_pmu.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_adc.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_dbg.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_dma.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_fmc.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_i2c.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_spi.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_qspi.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_gpio.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_exti.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_eclic.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_efuse.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_timer.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_usart.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_wwdgt.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_fwdgt.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_syscfg.c \


C_INCS = \
	-I$(CSL_DIR) \
	-I$(CSL_DIR)/RISCV/core \
	-I$(CSL_DIR)/GD32VW55x_standard_peripheral \
	-I$(CSL_DIR)/GD32VW55x_standard_peripheral/Include \

C_DEFS = \
	-DUSE_STDPERIPH_DRIVER \


vpath %.S . $(dir $(CSL_DIR))
S_SRCS = \
	CSL/RISCV/startup/entry.S \
	CSL/RISCV/startup/start.S

S_INCS = 

S_DEFS = 


MACHINE = -march=rv32imac_zicsr_zifencei -mabi=ilp32 -msmall-data-limit=8
CFLAGS  = $(MACHINE)
SFLAGS  = $(MACHINE)
LDFLAGS = $(MACHINE) -nostartfiles -specs=nano.specs
