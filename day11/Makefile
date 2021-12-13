CPP=g++
CFLAGS= -Wall -g
SRCS=day11.cc
OBJS=$(SRCS:.cc=.o)
PROG=day11

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
