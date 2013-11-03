CC ?= gcc
CFLAGS ?= -Wall
LIBS ?= -lcheck -lm
TESTSFILES = `find tests/ -type f -name "*.c"`

all: test compile

test:
	$(CC) $(CFLAGS) -o tests/tests_exec $(TESTSFILES) $(LIBS)
	tests/tests_exec
	rm -f tests/tests_exec

compile:
	./waf configure
	./waf build
