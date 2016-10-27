CFLAGS = `pkg-config --cflags check`
LIBS = `pkg-config --libs check`
VPATH=..

TEST_OBJECTS = test_motor.o mock_gpio.o mock_time.o

all: test_motor
	./test_motor

full: all memtest

test_motor: motor.o $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: test_motor
	CK_FORK=no valgrind --leak-check=full ./test_motor

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f test_motor
