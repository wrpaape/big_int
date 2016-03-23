BINNAME	= main
HEADMOD = big_int
SUBMODS = mem_mgmt string_io

SRCSDIR = ./$(HEADMOD)
DEPSDIR = $(SRCSDIR)
OBJSDIR = ../obj
DESTDIR = ../bin

MAINBIN	= $(DESTDIR)/$(PROG)

MODULES	= $(HEADMOD) $(SUBMODS)
SOURCES = $(patsubst %,$(SRCDIR)/%.c,$(MODULES))
OBJECTS = $(patsubst %,$(OBJDIR)/%.o,$(MODULES))

HEADSRC = $(patsubst %,$(SRCSDIR)/%.c,$(HEADMOD))
HEADOBJ = $(patsubst %,$(OBJSDIR)/%.o,$(HEADMOD))
GLOBDEP = $(patsubst %,$(DEPSDIR)/%.h,$(HEADMOD))

SUBSRCS = $(patsubst %,$(SRCSDIR)/%.c,$(SUBMODS))
SUBOBJS = $(patsubst %,$(OBJSDIR)/%.o,$(SUBMODS))
SUBDEPS = $(patsubst %,$(DEPSDIR)/%.h,$(SUBMODS))


CC	= gcc
CFLAGS	= -g -I$(SRCSDIR) -std=99 -Wall -D__USE_FIXED_PROTOTYPES__

all: $(MAINBIN)

$(MAINBIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(HEADOBJ): $(HEADSRC) $(GLOBDEP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SUBOBJS): $(SUBSRCS) $(SUBDEPS) $(GLOBDEP)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
