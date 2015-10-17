include Makefile.inc

CFLAGS=-Wall -pedantic -std=c11 -D_POSIX_C_SOURCE=199309L
LDFLAGS=-lrt -lpthread
EXE=conv
OBJ=src/convolution.o src/filters.o src/utils.o lib/ppm.o

.PHONY: clean

all: CFLAGS += -g
all: $(EXE)

release: CFLAGS += -O3
release: $(EXE)
	
$(EXE): src/main.o $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

test: LDFLAGS += -lcriterion
test: src/test.o $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(EXE) test $(OBJ) src/test.o src/main.o
