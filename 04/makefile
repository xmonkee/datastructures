GCC = gcc -fopenmp -Wall

all: singlesource allsources

verbose: GCC += -DVERBOSE
verbose: all

debug: GCC += -g
debug: all

singlesource:
	$(GCC) -o dijkstra_single graph.c dijkstra.c minpq_parallel.c \
		main.c

allsources:
	$(GCC) -o dijkstra_all graph.c dijkstra.c minpq.c \
		main.c -DALLSOURCES
