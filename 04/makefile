all: singlesource allsources

singlesource:
	gcc -o dijkstra_single graph.c dijkstra.c minpq_parallel.c \
		main.c -D SINGLESOURCE -fopenmp

allsources:
	gcc -o dijkstra_all graph.c dijkstra.c minpq.c \
		main.c -D ALLSOURCES -fopenmp

