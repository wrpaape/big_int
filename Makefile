CC     = gcc
FLAGS  = -g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS    = -ldl $(OPTLIBS)
PREFIX? = /usr/local

SOURCES=$(wildcard src/big_int/**/*.c src/big_int/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libbig_int.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
















# CC     = gcc
# CFLAGS = -g -Wall -D__USE_FIXED_PROTOTYPES__
# OBJS   = stat.o ch_type.o token.o in_file.o
# all: stat.out stat test.out
# test.out: test.c stat
# stat test.c >test.out
# # This generates a test output based on another example # in this book.
# stat.out: stat
# stat ../calc3/calc3.c >stat.out
# stat: $(OBJS)
# $(CC) $(CFLAGS) -o stat $(OBJS)
# stat.o: stat.c token.h
# $(CC) $(CFLAGS) -c stat.c
# ch_type.o: ch_type.c ch_type.h $(CC) $(CFLAGS) -c ch_type.c
# token.o: token.c token.h ch_type.h in_file.h $(CC) $(CFLAGS) -c token.c
# in_file.o: in_file.c in_file.h $(CC) $(CFLAGS) -c in_file.c
# clean:
# rm -f stat stat.o ch_type.o token.o in_file.o
