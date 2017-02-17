COMPILE := mpic++
FLAGS := -Wall -Isrc

SOURCES := $(shell find -type f -name '*.cc')
HEADERS := $(shell find -type f -name '*.h')
OBJECTS := $(SOURCES:cc=o)
TARGETS := main main.tar
TAR := Makefile src data/preprocessed_bts.csv


.PHONY: all clean run main.tar

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJECTS)

run: main
	mpirun -n 4 main


%.o: %.cc
	$(COMPILE) -c -o $@ $(FLAGS) $^

main: $(OBJECTS)
	$(COMPILE) -o $@ $(FLAGS) $^

main.tar:
	tar cf $@ $(TAR) --exclude "*.o"
