TOP=.

include $(TOP)/Makefile.inc

DIRS=firmware tests

.PHONY: all clean install rev $(DIRS) $(DIRS_REV)

all: CMD = make all
all: $(DIRS)

rev: CMD = make all
rev: $(DIRS_REV)

$(DIRS):
	$(CMD) -C $@

install: CMD = make install
install: $(DIRS)

clean: CMD = make clean
clean: $(DIRS) $(DIRS_REV)

