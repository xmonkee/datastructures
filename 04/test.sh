export OMP_NUM_THREADS=16
./dijkstra_single ./tests/test_graph.txt > test.out
export OMP_NUM_THREADS=1
./dijkstra_single ./tests/test_graph.txt >> test.out
export OMP_NUM_THREADS=16
./dijkstra_all ./tests/test_graph.txt >> test.out
export OMP_NUM_THREADS=1
./dijkstra_all ./tests/test_graph.txt >> test.out

