MPICC = mpicc
MPICFLAGS = -std=c99
MPICOPTFLAGS = -O2 -g -Wall
MPILDFLAGS =

teragen: teragen_main.c terarec.c
	$(MPICC) $(MPICFLAGS) $(MPICOPTFLAGS) -o $@ $^ $(MPILDFLAGS)

terasort: terasort_main.c terasort.c terarec.c
	$(MPICC) $(MPICFLAGS) $(MPICOPTFLAGS) -o $@ $^ $(MPILDFLAGS)

teravalidate: teravalidate_main.c teravalidate.c terarec.c
	$(MPICC) $(MPICFLAGS) $(MPICOPTFLAGS) -o $@ $^ $(MPILDFLAGS)

naivesort: naivesort.c terarec.c
	$(MPICC) $(MPICFLAGS) $(MPICOPTFLAGS) -o $@ $^ $(MPILDFLAGS)

.PHONY: clean

clean:
	rm -f *.o teragen terasort terapartition teravalidate terametrics naivesort data.dat splits.dat
