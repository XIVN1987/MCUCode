BUILD_DIR = build

EXE = GD32VW553xM

CSL_DIR = ../GD32VW553/CSL

include $(CSL_DIR)/CSL.mk


S_SRCS  = 

C_SRCS  = \
	FlashDev.c \
	FlashPrg.c \
	CSL/GD32VW55x_standard_peripheral/Source/gd32vw55x_fmc.c \

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
