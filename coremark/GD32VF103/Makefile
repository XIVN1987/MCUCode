BUILD_DIR = build

EXE = coremark


CSL_DIR = ../../board_GD32V/GD32VF103/CSL

include $(CSL_DIR)/CSL.mk


vpath %.c ..
C_SRCS += \
	hw_port.c \
	core_portme.c \
	coremark/core_main.c \
	coremark/core_util.c \
	coremark/core_state.c \
	coremark/core_matrix.c \
	coremark/core_list_join.c \

C_INCS += \
	-I. \
	-I../coremark \

C_DEFS += \
	-DITERATIONS=4000 \


OPT = -O2 -u _printf_float

LIBS =

LIBDIR = 

LDSCRIPT = $(CSL_DIR)/RISCV/startup/GD32VF103xB.lds

include $(CSL_DIR)/mkrules.mk
