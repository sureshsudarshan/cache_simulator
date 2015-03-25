# cache_simulator


					


		DESIGN AND IMPLEMENTATION OF A PARAMETRIC CACHE SIMULATOR SUITED FOR FFT

PROJECT OBJECTIVE:
To design a parametric cache simulator and use it to design data caches suited for FFT. 
CACHE MEMORY
A cache is a cache used by the CPU of a computer to reduce the average time to access memory. A cache is a smaller, faster memory which stores copies data from frequently used main memory locations. Most CPUs have independent caches namely data and instruction cache where the data cache is usually organized as a hierarchy of more cache levels (L1, L2 etc). When the processor needs to read from or write to a location in main memory, it first checks whether a copy of that data is in the cache. If so, the processor immediately reads from or writes to the cache, which is much faster than reading from or writing to main memory.
Most modern desktop and server CPUs have at least three independent caches: an instruction cache to speed up executable instruction fetch, a data cache to speed up data fetch and store, and a translation lookaside buffer (TLB) used to speed up virtual-to-physical address translation for both executable instructions and data. The data cache is usually organized as a hierarchy of more cache levels.

FORMULAE USED
Number of blocks =Cache Size/Block Size
Number of Sets=Number of blocks/Associativity
Set number=block number % number of sets
L1 hit Rate =(Read Hit+ Write Hit)/(Read Hit +Write Hit+ Read Miss+Write Miss) Miss Rate=(1-Hit Rate)
Victim cache Hit rate=(Read Hit + Write Hit)/Read Hit+Write Hit+Read Miss+Write Miss) Miss Rate=(1-Victim Cache Hit Rate)

SIMULATION RESULTS AND STATISTICS

1.	Number of L1 reads 
2.	Number of L1 read misses 
3.	Number of victim cache reads 
4.	Number of victim cache read misses 
5.	Number of L1 writes 
6.	Number of L1 write misses 
7.	Number of victim cache writes 
8.	Number of victim cache write misses 
9.	L1 miss rate 
10.	Victim cache miss rate 
11.	Total memory traffic to/from main memory  
COMPILING AND RUNNING SIMULATOR
The cache simulator accepts a trace file given as input and outputs various cache hits and misses. The trace file was run on a simple FFT program using the Intel’s Pintool.
L1 data cache takes in the following inputs from the user:

1)	Cache  size (in the powers of 2 )
2)	Block Size (in the powers of 2)
3)	Associativity (1 for fully associative, 2 for direct mapped cache, 3 for set associativity(The simulator will again ask for whether it is a 2,4 or 8 way associative)
4)	Write Policy (1 for Write through 2 for Write Back)
5)	Victim Cache Size ( in the powers of 2). 0 disables the victim cache.
The comments in the code provide more explanation about the snippets.





VALIDATION RUNS
Given values are L1 misses + Victim misses

•	But a highly-associative cache will have a lower miss rate  Each set has more blocks, so there’s less chance of a 
conﬂict between two addresses 
•	Overall, this will reduce AMAT and memory stall cycles.

Associativity reduces miss rate
L1 Cache Size=8192 bytes
Number of blocks=16
Victim Cache Size 1024

Associativity	Misses 	Write Policy
Direct	2451	1
2 way 	2170	1
4 way	2125	1
8 way	2097	1












Larger Block Size reduces miss rate with constant cache size and associativity
The ﬁgure below shows miss rates relative to block size and overall cache size 
1)	Smaller blocks do not take maximum advantage of spatial locality 
 2) But if blocks are too large, there are fewer blocks available, and more potential conﬂicts misses  
Cache Size 8192
Associativity: Direct
Victim Cache Size: 1024
Block Size	Misses	Write Policy 
4	12451	1
8	6284	1
16	3219	1
32	1654	1
64	832	1




‘







With Increasing Cache Size with constant block size and associativity
Performance decreases with increasing cache size considering constant block size and associativity
‘Block Size: 16 bytes
Associativity: 2 way associativity
Victim Cache Size: 1024
Cache Size	Misses	Write Policy
1024	565	1
2048	1092	1
4096	2150	1
8192	4235	1

Conclusion
Hence the results prove us that miss rates relative to the block size and overall cache size; smaller blocks do not take maximum advantage of spatial locality. But if blocks are too large, there will be fewer blocks available, and more potential misses due to conflicts.

References
 
1)	Computer Organization and Design, 4th Ed, D. A. Patterson and J. L. Hennessy 
2)	http://en.wikipedia.org/wiki/CPU_cache

