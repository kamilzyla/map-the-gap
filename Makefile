COMPILE := mpic++
FLAGS := -Wall -Isrc
SOURCES := $(shell find -type f -name '*.cc')
HEADERS := $(shell find -type f -name '*.h')


.PHONY: all clean main.tar

all: main main.tar

clean:
	rm -f main main.tar


main: Makefile $(SOURCES) $(HEADERS)
	$(COMPILE) $(FLAGS) -o $@ $(SOURCES)

main.tar: Makefile src data/preprocessed_bts.csv
	rm -f $@
	tar cf $@ $^
