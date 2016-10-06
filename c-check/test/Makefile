CFLAGS = `pkg-config --cflags check`
LIBS = `pkg-config --libs check`
VPATH=..

TEST_OBJECTS = test_launcher.o

all: test_launcher
	./test_launcher

full: all memtest

test_launcher: launch_program.o $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: test_launcher
	CK_FORK=no valgrind --leak-check=full ./test_launcher

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f test_launcher
