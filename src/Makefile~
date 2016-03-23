.PHONY: all clean

MAINMOD	= demo
ROOTMOD = big_int
SUBMODS = mem_mgmt string_io

MAINDIR = .
SRCSDIR = $(MAINDIR)/$(ROOTMOD)
DEPSDIR = $(SRCSDIR)
OBJSDIR = $(MAINDIR)/../obj
DESTDIR = $(MAINDIR)/../bin


ROOTSRC = $(patsubst %,$(SRCSDIR)/%.c,$(ROOTMOD))
ROOTOBJ = $(patsubst %,$(OBJSDIR)/%.o,$(ROOTMOD))
ROOTDEP = $(patsubst %,$(DEPSDIR)/%.h,$(ROOTMOD))

SUBSRCS = $(patsubst %,$(SRCSDIR)/%.c,$(SUBMODS))
SUBOBJS = $(patsubst %,$(OBJSDIR)/%.o,$(SUBMODS))
SUBDEPS = $(patsubst %,$(DEPSDIR)/%.h,$(SUBMODS)) $(ROOTDEP)

MAINSRC = $(patsubst %,$(MAINDIR)/%.c,$(MAINMOD))
MAINOBJ = $(patsubst %,$(OBJSDIR)/%.o,$(MAINMOD))
MAINDEP = $(ROOTDEP)

ALLOBJS = $(MAINOBJ) $(ROOTOBJ) $(SUBOBJS)

MAINBIN	= $(DESTDIR)/$(MAINMOD)


CC	= gcc
CFLAGS	= -g -I$(DEPSDIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

all: $(MAINBIN)

$(MAINBIN): $(ALLOBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(MAINOBJ): $(MAINSRC) $(MAINDEP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ROOTOBJ): $(ROOTSRC) $(ROOTDEP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SUBOBJS): $(SUBSRCS) $(SUBDEPS)
	$(CC) $(CFLAGS) -c -o $@ $(SUBSRCS)

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
