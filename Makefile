FLAGS := -std=c++11 -Wno-literal-suffix


.PHONY: all clean

all: hello

clean:
	rm -f hello


%: %.cc
	mpic++ $(FLAGS) -o $@ $<
