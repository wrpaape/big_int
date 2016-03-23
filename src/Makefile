.PHONY: all clean

MAINDIR = .
SRCSDIR = $(MAINDIR)/big_int
DEPSDIR = $(SRCSDIR)
OBJSDIR = $(MAINDIR)/../obj
DESTDIR = $(MAINDIR)/../bin


GLOBDEPS = $(DEPSDIR)/big_int_globals.h

globals_OBJ  = $(OBJSDIR)/big_int_globals.o
globals_SRC  = $(SRCSDIR)/big_int_globals.c
globals_DEPS = $(GLOBDEPS)
globals_PREQ = $(globals_SRC) $(globals_DEPS)

memory_OBJ  = $(OBJSDIR)/big_int_memory.o
memory_SRC  = $(SRCSDIR)/big_int_memory.c
memory_DEPS = $(DEPSDIR)/big_int_memory.h $(GLOBDEPS)
memory_PREQ = $(memory_SRC) $(memory_DEPS)

string_OBJ  = $(OBJSDIR)/big_int_string.o
string_SRC  = $(SRCSDIR)/big_int_string.c
string_DEPS = $(DEPSDIR)/big_int_string.h $(GLOBDEPS)
string_PREQ = $(string_SRC) $(string_DEPS)

demo_OBJ  = $(OBJSDIR)/demo.o
demo_SRC  = $(MAINDIR)/demo.c
demo_DEPS = $(DEPSDIR)/big_int.h
demo_PREQ = $(demo_SRC) $(demo_DEPS)

ALLMODS = demo globals memory string
ALLOBJS = $(foreach obj, $(ALLMODS), $($(obj)_OBJ))
BINFILE = $(DESTDIR)/demo


CC	= gcc
CFLAGS	= -g -I$(DEPSDIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

all: $(BINFILE)

$(BINFILE): $(ALLOBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(demo_OBJ): $(demo_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(globals_OBJ): $(globals_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(memory_OBJ): $(memory_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(string_OBJ): $(string_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
