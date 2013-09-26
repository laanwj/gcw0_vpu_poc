TOP=..
include $(TOP)/Makefile.inc

# _p1 for processor 1
BINS		= test1_p1.bin test2_p1.bin test3_p1.bin test4_p1.bin test5_p1.bin

GCC_ENDIAN_OPT	= -mel
LD_ENDIAN_OPT	= -EL
ABI_DIR		= el/mabi32
LDSCRIPT        = jz4770_p1.ld

#GCC_EXTRA_OPT   = -Wall -Wno-switch -Wpointer-arith -Wredundant-decls -O2 -pipe -ffast-math -fomit-frame-pointer
GCC_EXTRA_OPT   = -Wall -Wno-switch -mips32 -mno-abicalls -fno-pic -Wpointer-arith -Wredundant-decls -O2 -pipe -ffast-math -fomit-frame-pointer -mmxu

GCC_OPT		= $(GCC_ENDIAN_OPT) $(GCC_EXTRA_OPT) -I$(TOP)/include

all: $(BINS)

%.o:%.c
	$(CC) $(GCC_OPT) -c -o 	$@ 	$<

%.lib:%.o
	$(LD) -T $(LDSCRIPT) -nostdlib -static -o $@ $^

%.bin:%.lib
	$(OBJCOPY) -O binary $< 	$@

# Interface header deps
test4_p1.o: test4_p1.c test4_p1.h
	$(CC) $(GCC_OPT) -c -o 	$@ 	$<

test5_p1.o: test5_p1.c test5_p1.h
	$(CC) $(GCC_OPT) -c -o 	$@ 	$<

dep depend::

clean::
	rm -f *.o *~ *.s *.bin *.lib

.PHONY: libs clean dep depend 
