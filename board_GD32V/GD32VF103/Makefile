BUILD_DIR = build

EXE = GD32VF103

CSL_DIR = CSL

include $(CSL_DIR)/CSL.mk


C_SRCS += \
	main.c \

C_INCS += \
	-I. \


OPT = -O1 -g

LIBS =

LIBDIR = 

LDSCRIPT = $(CSL_DIR)/RISCV/startup/GD32VF103xB.lds

include $(CSL_DIR)/mkrules.mk
