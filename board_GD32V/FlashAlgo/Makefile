BUILD_DIR = build

EXE = GD32VF103xB

CSL_DIR = ../GD32VF103/CSL

include $(CSL_DIR)/CSL.mk


S_SRCS  = 

C_SRCS  = \
	FlashDev.c \
	FlashPrg.c \
	CSL/GD32VF103_standard_peripheral/Source/gd32vf103_fmc.c \

C_INCS += \
	-I. \

CFLAGS += -fpic -fno-jump-tables -ffreestanding
SFLAGS += -fpic -fno-jump-tables -ffreestanding
LDFLAGS+= -fpic -fno-jump-tables -ffreestanding


OPT = -O1

LIBS =

LIBDIR = 

LD_NO_GC = 1	# --gc-sections will discard all code

LDSCRIPT = FlashAlgo.ld

include $(CSL_DIR)/mkrules.mk
