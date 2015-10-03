include Makefile.inc

CFLAGS=-Wall -pedantic -std=c11
LDFLAGS=-lrt -lpthread
EXE=conv
OBJ=src/convolution.o src/filters.o src/utils.o lib/ppm.o

.PHONY: clean

all: CFLAGS += -g
all: $(EXE)

release: CFLAGS += -O3
release: $(EXE)
	
$(EXE): src/main.o $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

test: LDFLAGS += -lcriterion
test: src/test.o $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(EXE) test $(OBJ) src/test.o src/main.o
