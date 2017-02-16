COMPILE := mpic++
FLAGS :=
SOURCES := $(shell find -type f -name '*.cc')
HEADERS := $(shell find -type f -name '*.h')


.PHONY: all clean

all: main

clean:
	rm -f main


main: $(SOURCES) $(HEADERS)
	$(COMPILE) $(FLAGS) -o $@ $(SOURCES)
