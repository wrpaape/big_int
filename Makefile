.PHONY: all clean

SRCDIR = src
MFLAGS = -C -j5 LAST=550

all clean:
	$(MAKE) $(MFLAGS) $(SRCDIR) $@

