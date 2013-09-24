TOP=..
include $(TOP)/Makefile.inc

P1_SRC		= test1_p1.c
P1_BIN		= test1_p1.bin
P1_LIB		= test1_p1.lib
P1_OBJ		= test1_p1.o
P1_MID		= $(P1_OBJ:.o=.mid.s)
P1_ASM		= $(P1_OBJ:.o=.s)

GCC_ENDIAN_OPT	= -mel
LD_ENDIAN_OPT	= -EL
ABI_DIR		= el/mabi32

#GCC_EXTRA_OPT   = -Wall -Wno-switch -Wpointer-arith -Wredundant-decls -O2 -pipe -ffast-math -fomit-frame-pointer
GCC_EXTRA_OPT   = -Wall -Wno-switch -mips32 -mno-abicalls -fno-pic -Wpointer-arith -Wredundant-decls -O2 -pipe -ffast-math -fomit-frame-pointer -mmxu

GCC_OPT		= $(GCC_ENDIAN_OPT) $(GCC_EXTRA_OPT) -I$(TOP)/include

all: $(P1_BIN)

$(P1_OBJ):%.o:%.c
	$(CC) $(GCC_OPT) -c -o 	$@ 	$<
$(P1_LIB): $(P1_OBJ) 
	$(LD) -T test1_p1.ld -nostdlib -static -o $@ $^
$(P1_BIN): $(P1_LIB)
	$(OBJCOPY) -O binary $< 	$@

dep depend::

clean::
	rm -f *.o *~ *.s *.bin *.lib

.PHONY: libs clean dep depend 
