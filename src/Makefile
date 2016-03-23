.PHONY: all clean

MAINDIR = .
SRCSDIR = $(MAINDIR)/big_int
DEPSDIR = $(SRCSDIR)
OBJSDIR = $(MAINDIR)/../obj
DESTDIR = $(MAINDIR)/../bin


GLOBDEPS = $(DEPSDIR)/big_int.h

big_int_OBJ  = $(OBJSDIR)/big_int.o
big_int_SRC  = $(SRCSDIR)/big_int.c
big_int_DEPS = $(GLOBDEPS)
big_int_PREQ = $(big_int_SRC) $(big_int_DEPS)

mem_mgmt_OBJ  = $(OBJSDIR)/mem_mgmt.o
mem_mgmt_SRC  = $(SRCSDIR)/mem_mgmt.c
mem_mgmt_DEPS = $(DEPSDIR)/mem_mgmt.h $(GLOBDEPS)
mem_mgmt_PREQ = $(mem_mgmt_SRC) $(mem_mgmt_DEPS)

string_io_OBJ  = $(OBJSDIR)/string_io.o
string_io_SRC  = $(SRCSDIR)/string_io.c
string_io_DEPS = $(DEPSDIR)/string_io.h $(GLOBDEPS)
string_io_PREQ = $(string_io_SRC) $(string_io_DEPS)

demo_OBJ  = $(OBJSDIR)/demo.o
demo_SRC  = $(MAINDIR)/demo.c
demo_DEPS = $(GLOBDEPS)
demo_PREQ = $(demo_SRC) $(demo_DEPS)

ALLMODS = demo big_int mem_mgmt string_io
ALLOBJS = $(foreach obj, $(ALLMODS), $($(obj)_OBJ))
BINFILE = $(DESTDIR)/demo


CC	= gcc
CFLAGS	= -g -I$(DEPSDIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

all: $(BINFILE)

$(BINFILE): $(ALLOBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(demo_OBJ): $(demo_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(big_int_OBJ): $(big_int_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(mem_mgmt_OBJ): $(mem_mgmt_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(string_io_OBJ): $(string_io_PREQ)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCSDIR)/*~ $(DEPSDIR)/*~ $(OBJSDIR)/*.o $(MAINBIN)
