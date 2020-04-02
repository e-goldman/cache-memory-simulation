# cache-memory-simulation
Software simulation of a cache memory subsystem using C++


While studying CPU and memory architecture at BU, I was asked to design a program to demonstrate the behavior of a CPU cache
and its interaction with main memory.

According to problem specifications, the simulation functions as a direct-mapped, write-back cache with 16 slots each containing
a block with a capacity of 16 bytes.

As a direct-mapped cache, each address in main memory can only be saved in one place in the cache.
If that cache slot is already in use at the time of a request, it is overwritten. Therefore, no replacement policy
is needed.

A write-back cache tracks which entries are changed (thereby making them out of synch with the corresponding main mem address)
by marking them as "dirty," typically with a 1-bit flag. The altered data in these entries is not written back to main mem until
that cache slot is needed for something else.

A 16-slot cache of 16-byte blocks is unrealistically small for the sake of a manageable concept demonstration.

The program supports three types of requests, Read byte, Write byte, and Display cache.

(R)ead - ask which main mem address (represented by an array - see line 28 in my code) should be read from, check if that 
address is saved in the cache (represented by an array of structs - see line 10), and do one of the following:
  - if the address is present, display the value it holds and indicate "cache hit"
  - if it is absent, copy the block to the cache from memory, then display the value and indicate "cache miss"
  
(W)rite - ask which address should be written to and the data value to be written, check if it's in the cache, and again either
record the data to the cache and indicate "cache hit" or bring the block in from memory first and indicate "cache miss."

(D)isplay - output the contents all cache slots in a table.

In the background, whenever a cache slot needs to be overwritten by another memory address, the program checks the dirty bit
(see lines 71 and 102) and updates the main mem array when needed.

To better facilitate bugtesting and grading assessment, a predetermined list of requests and i/o values was provided.
These are hard-coded in this version of my code (see lines 48 and 49).


To-do:

I'd like to modify this to accept user inputs instead of following a predetermined set of requests so one can better use the
program to play around with and observe cache behavior.
