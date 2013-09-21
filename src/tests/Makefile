TOP=..
include $(TOP)/Makefile.inc

COMMON_FLAGS +=
CFLAGS += -DDUMP
CXXFLAGS += 
LDFLAGS +=

TARGETS = poc

ETNA_OBJS =

all: $(TARGETS)

clean:
	rm -f *.o
	rm -f $(TARGETS)

poc: poc.o $(ETNA_OBJS)
	$(CXX) $(CFLAGS) -o $@ $^  $(LDFLAGS)

