COMPILE := mpic++
FLAGS := -std=c++11 -Wno-literal-suffix


.PHONY: all clean

all: job

clean:
	rm -f job


%: %.cc
	$(COMPILE) $(FLAGS) -o $@ $<
