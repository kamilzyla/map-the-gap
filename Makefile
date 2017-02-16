COMPILE := mpic++
FLAGS :=


.PHONY: all clean

all: job

clean:
	rm -f job


%: %.cc
	$(COMPILE) $(FLAGS) -o $@ $<
