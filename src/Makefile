.PHONY: all clean

MAINDIR = .
SRCSDIR = $(MAINDIR)/big_int
DEPSDIR = $(SRCSDIR)
OBJSDIR = $(MAINDIR)/../obj
DESTDIR = $(MAINDIR)/../bin


GLOBDEPS = $(DEPSDIR)/globals.h

globals_OBJ  = $(OBJSDIR)/globals.o
globals_SRC  = $(SRCSDIR)/globals.c
globals_DEPS = $(GLOBDEPS)
globals_PREQ = $(globals_SRC) $(globals_DEPS)

utils_OBJ  = $(OBJSDIR)/utils.o
utils_SRC  = $(SRCSDIR)/utils.c
utils_DEPS = $(DEPSDIR)/utils.h $(GLOBDEPS)
utils_PREQ = $(utils_SRC) $(utils_DEPS)

memory_OBJ  = $(OBJSDIR)/memory.o
memory_SRC  = $(SRCSDIR)/memory.c
memory_DEPS = $(DEPSDIR)/memory.h $(GLOBDEPS)
memory_PREQ = $(memory_SRC) $(memory_DEPS)

add_OBJ  = $(OBJSDIR)/add.o
add_SRC  = $(SRCSDIR)/add.c
add_DEPS = $(DEPSDIR)/add.h $(DEPSDIR)/subtract.h $(DEPSDIR)/memory.h $(DEPSDIR)/multiply.h $(DEPSDIR)/utils.h $(GLOBDEPS)
add_PREQ = $(add_SRC) $(add_DEPS)

subtract_OBJ  = $(OBJSDIR)/subtract.o
subtract_SRC  = $(SRCSDIR)/subtract.c
subtract_DEPS = $(DEPSDIR)/subtract.h $(DEPSDIR)/add.h $(DEPSDIR)/memory.h $(DEPSDIR)/multiply.h $(DEPSDIR)/utils.h $(GLOBDEPS)
subtract_PREQ = $(subtract_SRC) $(subtract_DEPS)

multiply_OBJ  = $(OBJSDIR)/multiply.o
multiply_SRC  = $(SRCSDIR)/multiply.c
multiply_DEPS = $(DEPSDIR)/multiply.h $(DEPSDIR)/memory.h $(GLOBDEPS)
multiply_PREQ = $(multiply_SRC) $(multiply_DEPS)

string_OBJ  = $(OBJSDIR)/string.o
string_SRC  = $(SRCSDIR)/string.c
string_DEPS = $(DEPSDIR)/string.h $(DEPSDIR)/digits.h $(GLOBDEPS)
string_PREQ = $(string_SRC) $(string_DEPS)

digits_OBJ  = $(OBJSDIR)/digits.o
digits_SRC  = $(SRCSDIR)/digits.c
digits_DEPS = $(DEPSDIR)/digits.h $(GLOBDEPS)
digits_PREQ = $(digits_SRC) $(digits_DEPS)

demo_OBJ  = $(OBJSDIR)/demo.o
demo_SRC  = $(MAINDIR)/demo.c
demo_DEPS = $(MAINDIR)/big_int.h
demo_PREQ = $(demo_SRC) $(demo_DEPS)

ALLMODS = demo globals utils memory add subtract multiply string digits
ALLOBJS = $(foreach obj, $(ALLMODS), $($(obj)_OBJ))
BINFILE = $(DESTDIR)/demo


CC	= gcc
CFLAGS	= -g -I$(MAINDIR) -std=c99 -fstrict-aliasing -Wall -D__USE_FIXED_PROTOTYPES__

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

$(subtract_OBJ): $(subtract_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(multiply_OBJ): $(multiply_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(string_OBJ): $(string_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(digits_OBJ): $(digits_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
