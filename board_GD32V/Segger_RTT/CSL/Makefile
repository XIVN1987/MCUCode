
C_SRCS = \
	CSL/RISCV/core/n200_func.c \
	CSL/RISCV/stubs/sbrk.c \
	CSL/RISCV/startup/handlers.c \
	CSL/GD32VF103_standard_peripheral/system_gd32vf103.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_gpio.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_rcu.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_timer.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_eclic.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_exti.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_pmu.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_usart.c \

C_INCS = \
	-ICSL \
	-ICSL/RISCV/core \
	-ICSL/GD32VF103_standard_peripheral \
	-ICSL/GD32VF103_standard_peripheral/Include \

C_DEFS = \
	-DUSE_STDPERIPH_DRIVER \
	-DGD32VF103C_START

S_SRCS = \
	CSL/RISCV/startup/entry.S \
	CSL/RISCV/startup/start.S

S_INCS = 

S_DEFS = 

LIBS = -nostartfiles
LIBDIR = 

MACHINE = -march=rv32imac_zicsr_zifencei -mabi=ilp32 -msmall-data-limit=8
CFLAGS = $(MACHINE)
SFLAGS = $(MACHINE)

LDSCRIPT = CSL/RISCV/startup/GD32VF103xB.lds
LDFLAGS  = $(MACHINE) -specs=nano.specs -T$(LDSCRIPT)
