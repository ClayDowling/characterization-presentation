.PHONY: all test clean

CFLAGS = -g

all: test life

clean:
	$(MAKE) -C test clean
	rm -f *.o
	rm -f life

test:
	$(MAKE) -C test full

launcher: launch_program.o main.o
	$(CC) $(CFLAGS) -o $@ $^
