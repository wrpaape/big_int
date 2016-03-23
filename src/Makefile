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

# SUBSRCS = $(patsubst %,$(SRCSDIR)/%.c,$(SUBMODS))
# SUBOBJS = $(patsubst %,$(OBJSDIR)/%.o,$(SUBMODS))
# SUBDEPS = $(patsubst %,$(DEPSDIR)/%.h,$(SUBMODS)) $(ROOTDEP)

MAINSRC = $(patsubst %,$(MAINDIR)/%.c,$(MAINMOD))
MAINOBJ = $(patsubst %,$(OBJSDIR)/%.o,$(MAINMOD))
MAINDEP = $(ROOTDEP)

ALLOBJS = $(MAINOBJ) $(ROOTOBJ) $(SUBOBJS)

MAINBIN	= $(DESTDIR)/$(MAINMOD)

define MAKEOBJ =
$(1): $(2) $(3)
	$(CC) $(CFLAGS) -c -o $@ $<
endef
OBJSRCDEP = $(OBJSDIR)/$(1).o $(SRCSDIR)/$(1).c $(DEPSDIR)/$(1).h

SUBOSD    = $(call OBJSRCDEP,$(1)) $(ROOTDEP)


CC	= gcc
CFLAGS	= -g -I$(DEPSDIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

all:
	@echo $(call SUBOSD,mem_mgmt)
# all: $(MAINBIN)

# $(MAINBIN): $(ALLOBJS)
# 	$(CC) $(CFLAGS) -o $@ $^

# $(MAINOBJ): $(MAINSRC) $(MAINDEP)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# $(ROOTOBJ): $(ROOTSRC) $(ROOTDEP)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# $(foreach mod,$(SUBMODS),$(eval $(call MAKEOBJ,$(call SUBOSD,$(mod)))))

# $(SUBOBJS): $(SUBSRCS) $(SUBDEPS)
# 	$(CC) $(CFLAGS) -c -o $@ $(SUBSRCS)

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
