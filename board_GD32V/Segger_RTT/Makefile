BUILD_DIR = build

EXE = Segger_RTT

CSL_DIR = ../GD32VF103/CSL

include $(CSL_DIR)/CSL.mk


C_SRCS += \
	main.c \
	RTT/SEGGER_RTT.c \
	RTT/SEGGER_RTT_printf.c

C_INCS += \
	-I. \
	-IRTT \


OPT = -O1 -g

LIBS =

LIBDIR = 

LDSCRIPT = $(CSL_DIR)/RISCV/startup/GD32VF103xB.lds

include $(CSL_DIR)/mkrules.mk
