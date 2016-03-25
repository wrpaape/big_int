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

utils_OBJ  = $(OBJSDIR)/big_int_utils.o
utils_SRC  = $(SRCSDIR)/big_int_utils.c
utils_DEPS = $(DEPSDIR)/big_int_utils.h $(GLOBDEPS)
utils_PREQ = $(utils_SRC) $(utils_DEPS)

memory_OBJ  = $(OBJSDIR)/big_int_memory.o
memory_SRC  = $(SRCSDIR)/big_int_memory.c
memory_DEPS = $(DEPSDIR)/big_int_memory.h $(GLOBDEPS)
memory_PREQ = $(memory_SRC) $(memory_DEPS)

add_OBJ  = $(OBJSDIR)/big_int_add.o
add_SRC  = $(SRCSDIR)/big_int_add.c
add_DEPS = $(DEPSDIR)/big_int_add.h $(DEPSDIR)/big_int_memory.h $(DEPSDIR)/big_int_mult.h $(DEPSDIR)/big_int_utils.h $(GLOBDEPS)
add_PREQ = $(add_SRC) $(add_DEPS)

mult_OBJ  = $(OBJSDIR)/big_int_mult.o
mult_SRC  = $(SRCSDIR)/big_int_mult.c
mult_DEPS = $(DEPSDIR)/big_int_mult.h $(DEPSDIR)/big_int_memory.h $(GLOBDEPS)
mult_PREQ = $(mult_SRC) $(mult_DEPS)

string_OBJ  = $(OBJSDIR)/big_int_string.o
string_SRC  = $(SRCSDIR)/big_int_string.c
string_DEPS = $(DEPSDIR)/big_int_string.h $(GLOBDEPS)
string_PREQ = $(string_SRC) $(string_DEPS)

demo_OBJ  = $(OBJSDIR)/demo.o
demo_SRC  = $(MAINDIR)/demo.c
demo_DEPS = $(DEPSDIR)/big_int.h
demo_PREQ = $(demo_SRC) $(demo_DEPS)

ALLMODS = demo globals utils memory add mult string
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

$(utils_OBJ): $(utils_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(memory_OBJ): $(memory_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(add_OBJ): $(add_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(mult_OBJ): $(mult_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(string_OBJ): $(string_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
