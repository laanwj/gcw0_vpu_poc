TOP=..
include $(TOP)/Makefile.inc

COMMON_FLAGS +=
CFLAGS += -DDUMP
CXXFLAGS += 
LDFLAGS +=

TARGETS = poc poc_fb mxu poc_mem poc_irq poc_dma

ETNA_OBJS =

all: $(TARGETS)

clean:
	rm -f *.o
	rm -f $(TARGETS)

poc: poc.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

poc_fb: poc_fb.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

poc_mem: poc_mem.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

poc_irq.o: poc_irq.c ../firmware/test4_p1.h

poc_irq: poc_irq.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

poc_dma.o: poc_dma.c ../firmware/test5_p1.h

poc_dma: poc_dma.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

mxu: mxu.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)
