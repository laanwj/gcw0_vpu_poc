TOP=..
include $(TOP)/Makefile.inc

COMMON_FLAGS +=
CFLAGS += -DDUMP
CXXFLAGS += 
LDFLAGS +=

TARGETS = poc mxu

ETNA_OBJS =

all: $(TARGETS)

clean:
	rm -f *.o
	rm -f $(TARGETS)

poc: poc.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

mxu: mxu.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

