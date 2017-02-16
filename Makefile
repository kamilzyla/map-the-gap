COMPILE := mpic++
FLAGS := -Wall
SOURCES := $(shell find -type f -name '*.cc')
HEADERS := $(shell find -type f -name '*.h')


.PHONY: all clean

all: main src.tar

clean:
	rm -f main src.tar


main: $(SOURCES) $(HEADERS)
	$(COMPILE) $(FLAGS) -o $@ $(SOURCES)

src.tar: $(SOURCES) $(HEADERS)
	tar cf $@ src
