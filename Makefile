COMPILE := mpic++
FLAGS :=
SOURCES := $(wildcard *.cc)


.PHONY: all clean

all: main

clean:
	rm -f main


main: $(SOURCES)
	$(COMPILE) $(FLAGS) -o $@ $(SOURCES)
