CFLAGS=-Wall -pedantic -std=c11 -g
LDFLAGS=-lrt -lpthread
EXE=conv
OBJ=src/main.o src/convolution.o src/filters.o lib/ppm.o

.PHONY: clean

all: $(EXE)
	
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(EXE) $(OBJ)
