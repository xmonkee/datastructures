Dijkstra's algorithm for single and multiple sources in parallel
Author: Mayank Mandava

Usage:
   Compilation: just run "make"
   Executables: dijkstra_single and dijkstra_all
   Usage: $executable graphfile
   Graphfile: Should be in the format: "source  target  weight"

Output:
   Both executables will show number of threads utilized and running 
   time on screen.

Verbose:
   To see the detailed output of dijkstra, run "make verbose"
   This will require running any program as "$executable graphfile outputfile"
   If you run dijkstra_all with "verbose" option, the output file can get
   VERY large. I do not recommend doing this. 

Controlling parallel execution:
   Both algorithms are parallel (explained below) by default. To control
   the parallelization, use environemnt variables:

   "export OMP_NUM_THREADS=1" for non-parallel
   "export OMP_NUM_THREADS=16" for parallel

Algorithms:
   Single source:
      To parellize the single source algorithms, I have focused on the 
      extraction of the minimum weight vertex from the pool of "uncompleted" 
      vertices that is a key step of Dijkstra's algorithms.
      The pool is divided into chunks and a minimum (if any vertices are 
      eligible) is selected from each. Then a minimum of these minimas is 
      selected. The paralellization happens in the selection of the local 
      minima. The threads are then synchronized to find the global minima.

      Pseudocode for priority queue operations:
         extract_minima():
            divide vertices into T pools of size |V|/T
            for each pool S:
               found_local_min_S = false
               for each vertex in pool:
                  if vertex is "unextracted":
                     if !found_local_min_S:
                        minS = vertex
                        found_local_min = true
                     else if d[vertex] < d[minS]:
                        local_min = vertex
            let minS be the vertex with the minimum distance in pool S
            A similar reduction procedure is applied to min1, min2...minT to find global minima
            return global minima
      The rest of the algorithms is same as dijkstra. 
   
      Running Time:
         Normally we get O(V^2). With paralellization: O(V*(V/T+T)) where T is number of threads.
         Each local minima search takes V/T and the global minima search takes an addtional T. 

   All Sources:
      This one is straightforward. We just divide the vertices between 
      threads and run dijkstra-single-source on each vertex
      Running Time: O(V^3/T)

Speedup:
   using linux2.cs.uchicago.edu on 16 cores
   Single Source: 4x
   All Sources: 10x

Running time of single source on provided graph:
   Running Dijkstra Single Source
   Number of threads: 16
   Time taken: 88.0

   Running Dijkstra Single Source
   Number of threads: 1
   Time taken: 330.0

Running time of all-sources on a graph with 5000 vertices:
   Running Dijkstra All Sources
   Number of threads: 16
   Time taken: 73.0

   Running Dijkstra All Sources
   Number of threads: 1
   Time taken: 834.0

Files:
   graph.c: graph functions
   minpq.c: array based priority queue, non parallel
   minpq_parallel.c: array based priority queue, parallel
   dijkstra.c: dijkstra's algorithms. Calls minpq and graph functions
   main.c: Executable. Calls dijskstra on single or all vertices
   dijskstra_single is compiled with minpq_parallel.c and dijkstra_all is 
   compiled with minpq.c. They offer a common interface and are 
   interchangeable. 


