CPP=g++
CFLAGS= -Wall -g
SRCS=day02.cc
OBJS=$(SRCS:.cc=.o)
PROG=day02

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJS)
	$(CPP) $(CFLAGS) -o $(PROG) $(OBJS)

test: $(PROG)
	./$(PROG) input_test.txt

run: $(PROG)
	./$(PROG) input.txt

clean:
	rm -f $(OBJS) $(PROG)
