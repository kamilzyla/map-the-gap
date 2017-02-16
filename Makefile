COMPILE := mpic++
FLAGS := -Wall
SOURCES := $(shell find -type f -name '*.cc')
HEADERS := $(shell find -type f -name '*.h')


.PHONY: all clean

all: main

clean:
	rm -f main code.tar


main: $(SOURCES) $(HEADERS)
	$(COMPILE) $(FLAGS) -o $@ $(SOURCES)

code.tar: clean
	tar cf $@ * --exclude "startup_script"
