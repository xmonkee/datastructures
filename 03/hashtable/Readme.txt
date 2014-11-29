Hashtable

compilation: gcc *.c -o dict

files:
   interactive.c - User Interface
   chtbl.c - Hashtable implementation and interface to UI
   list.c - list datastructure

Logging: The logfile is by default "chtbl.log". This can be changed in chtbl.h

Rehashing: Initial buckets = 100. When the load factor becomes more than [3.0], we rehash by doubling number of buckets. When the load factor becomes less than [1], we rehash by halving the number of buckets. Both these numbers are configurable in chtbl.h. Rehashing is done by doubling buckets till next rehash to preserve O(1) ammortized time. Rehashing is done on the way down to preserve memory.

Logging terms:
   Load Factor: #items/#buckets
   #items: total items stored in hashtable
   #buckets: number of buckets at current time
   #buckets used: buckets with at least 1 item
   Occupancy: Is calculted using an bit array and observing when we add an element to a previously unoccupied basked and when we remove the last element from some array. 

Hash functions: 3 hashfunctions are implemented and can be chosen by #defining either HASH1 HASH2 or HASH3 in chtbl.h. More details in source file.

On avearge, these were the occupancy rates(#buckets used / #buckets at rehashing time) we got from the 3 hash functions

HASH1: 81% 
HASH2: 72% 
HASH3: 74% 

Surprisingly, HASH1, the simplest hash function performed the best. But this is likely due to the varied nature of the keys in the test dictionaries. 


