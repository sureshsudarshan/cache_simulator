#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
#define TRUE 1
#define FALSE 0


//#define DEFAULT_CACHE_SIZE (8 * 1024)
//#define DEFAULT_CACHE_BLOCK_SIZE 1
//#define DEFAULT_CACHE_ASSOC 1
//#define DEFAULT_CACHE_WRITEBACK TRUE
//#define DEFAULT_CACHE_NOWRITEALLOC FALSE
//#define DEFAULT_VICTIMCACHE_SIZE 16

void read_write();
void cache_victim();
void lrupolicy();

typedef struct // cache structure
{
int tag;
int index;
int data;
int validbit;
int dirtybit;
} cachestructure;
cachestructure mycache;
typedef struct	// victim cache
{
int tag;
int data;
int validbit;
} victimcache;



int main()
{

int i,j,counter[1000],vcounter[1000];
int z=1,v=1;
float L1rate,victimrate;
int l,lru,done;
int ch,y,m;
int hit,victimhit;
int cachesize,blocksize,assoc,victimsize;
int total_trace;
int writepolicy;
int number_of_blocks,tag_bits,victim_blocks,index;
int choose,read,write;
unsigned char  add[1000000],data[1000000];
//unsigned int ls[10000];
unsigned char  ls[100000];
int cache_hit,cache_miss,victimcache_hit,victimcache_miss;
int cache_write_hit,cache_write_miss,victimcache_write_hit,victimcache_write_miss;
int traffic =0;
int b,c,d;
FILE *trace;
trace=fopen("/home/suresh_sudarshan/Downloads/trace4.txt","rb");
if(trace != NULL)
{
total_trace =0;

for(i = 1;feof(trace)==0;i++)
{
//fscanf(trace,"%d",&ls[i]);
fscanf(trace,"%c",&add[i]);
//sscanf(add[i],"%c",b);
//strtol(add[i],NULL,16);
fscanf(trace,"%c",&ls[i]);
fscanf(trace,"%c",&data[i]);
//strtol(data[i],NULL,16);
//printf("hi");
//printf("add[%d]= %d", i,ls[i]);
total_trace =total_trace +1;

}
}
unsigned int htoi(const char add[]){
unsigned int n=0;
i=0;
if(add[i]==0 && add[i+1]=='x'){
i=i+2;
}
while(add[i]!='\0'){
n=n * 16;
if(add[i]>='0' && add[i] <= '9')
{
n=n + (add[i] - '0');
}
else if(tolower(add[i]) >= 'a' && tolower(add[i]) <= 'f')
{
n = n + (tolower(add[i]) - 'a') + 10;
}
i++;
}
return n;
}

char *getBinary(unsigned int num)
{
char* bstring;
int i;
bstring=(char*)malloc(sizeof(char) * 33);
assert(bstring != NULL);
bstring[32]= '\0';
for(i=0;i<32;i++)
{bstring[32-1-i]= (num==((1<<i) | num)) ? '1' : '0';
}
return bstring;
}
char *formatBinary(char *bstring)
{
char *formatted;
int i;
formatted=(char *) malloc(sizeof(char) * (32+3));
assert(formatted!=NULL);
formatted[32+2]= '\0';
for(i=0;i<mycache.tag;i++)
{
formatted[i]=bstring[i];
}
formatted[mycache.tag]=' ';
for(i=(mycache.tag)+1;i<(mycache.tag);i++)
{
formatted[i]=bstring[i-1];
}
formatted[mycache.index+mycache.tag+1]= ' ';
for(i=(mycache.index)+(mycache.tag)+2;i<(mycache.data)+(mycache.index)+(mycache.tag+2);i++)
{
formatted[i]=bstring[i-2];
}
return formatted;
}

void lrupolicy()
{
lru = i- number_of_blocks-1;
   for (l = i-1; l > lru; l--) //Searching through L1 for the least recently used value                                             
{
 done =0;
 for (m= l+1; m<i+1;m++)
 {
 if(done != 1)
  {
 if (add[l] == add[m])
  {
  lru--;
   done = 1;
           }
  else
     {
          }
          }
           }
            }
}

//printf("\nEnter CACHE input values to the simulator\n");
printf("\nL1 CACHE \n");
printf("Enter Data Cache Size Enter in Bytes:\t");
scanf("%d",&cachesize);
printf("Enter Cache Block Size in Bytes:\t");
scanf("%d",&blocksize);
printf("Choose Associativity:   1.Fully Associated \t  2.Direct Mapped \t 3.Set Associated: \t");
scanf("%d",&assoc);
printf("Choose WritePolicy:   1.Write Back with Write Allocate \t  2.Write Through with NoAllocate:\t");
scanf("%d",&writepolicy);
printf("\nVictim Cache Size\n");
printf(" Enter Victim Cache Size :\t");
scanf("%d",&victimsize);


cachestructure cache_l[cachesize];
victimcache victimcache_l[victimsize];


void cache_victim()
{
 for (i = 0;i<number_of_blocks;i++)  // initilized cache as empty
        {
                cache_l[i].tag = '0';
                cache_l[i].index ='0';
                cache_l[i].data = '0';
                cache_l[i].validbit =0;
                cache_l[i].dirtybit = 0;
        }
        for (i = 0;i< victim_blocks;i++) // initialized victim cache as empty
        {
                victimcache_l[i].tag = '0';
                victimcache_l[i].data ='0';
                victimcache_l[i].validbit = 0;
        }
}


/****************************************************************FULLY ASSCOCIATIVE************************************************************* */

if(assoc ==1 )
{
cache_hit =0;cache_miss = 0;
cache_write_hit =0; cache_write_miss =0;
victimcache_hit =0,victimcache_miss = 0;
victimcache_write_hit =0,victimcache_write_miss =0;

number_of_blocks  = cachesize/(blocksize);
victim_blocks = (victimsize)/(blocksize);
printf("\nNumber of Blocks = %d",number_of_blocks);
printf("\nVictimcache Blocks = %d",victim_blocks);
//tag_bits = 32 -  log(number_of_blocks)/log(2);
//printf("\ntag_bits = \t%d\n",tag_bits);

cache_victim();
	    

	for (i=1;i<total_trace;i++)       // starting the trace file to check the match
	{
	if(ls[i] == 'R')     // for read
		{
		hit = 0,victimhit =0;

		//Checking in Cache for cache Hit
														
		for (j=1;j<number_of_blocks+1;j++)
			{
			if (hit != 1) 			// Checking for hit

			{

				if( cache_l[j].validbit == 0 )

				{
									
				
				}

				if(cache_l[j].validbit == 1) // cache Hit

				{



					if (add[i] == cache_l[j].tag)

					{



						hit =1;cache_hit++;

						cache_hit = cache_hit +1;cache_hit++;

					}

				}

			}

			}



		//Checking in Victim Cache for Victim Hit

		for (j=1;j<victim_blocks+1;j++)

		{

			if (hit != 1 && victimhit ==0)  // Checking for Victim Hit

			{

				if (victimcache_l[j].validbit ==0)

				{

				}

				else

				{

					if (victimcache_l[j].tag == add[i]) //Victim Hit

					{

						victimhit = 1;

						victimcache_hit = victimcache_hit+1;

						cache_miss = cache_miss+1;

						y = j; 	 		// if hit y value used for swap

					}

				}

			}

		}



		// Cache Miss and Victim Miss Occurs

		if(hit != 1 && victimhit != 1)

		{

			if (z< number_of_blocks+1 && victim_blocks >= 0)

				for(i=1;i<number_of_blocks+1;i++){


                    {

						cache_l[z].validbit = 1;

						cache_l[z].tag = add[i];

						cache_miss = cache_miss +1;

						victimcache_miss = victimcache_miss +1;

						z = z+1;

						traffic++;

                    }}

			else        // if Cache is full

			{

				lrupolicy();     // Least replacement Policy

				int r;

				l= l+1;          // which place to add the block in cache using LRU policy

				for(r =1; r < number_of_blocks + 1 ;r++) // final checking

				{

					if (add[l] == cache_l[r].tag)

					{

						cache_l[r].validbit = 1;

						cache_l[r].tag = add[i];

						cache_miss = cache_miss +1;

						if (v< victim_blocks+1)

						{

							victimcache_l[v].validbit = 1;

							victimcache_l[v].tag= add[l];

							victimcache_miss = victimcache_miss+1;

							v = v+1;

						}

						cache_l[r].validbit = 1;

						cache_l[r].tag = add[i];

						cache_miss = cache_miss +1;

						traffic++;
						
					}

				}

			}

		}



		// Cache Miss and Victim Hit Occurs

		if (hit != 1 && victimhit ==1)

		{

			lrupolicy();  // LRU policy



			int r,wait;   //final check

			l= l+1;

			for(r =1; r < number_of_blocks + 1 ;r++)

			{

				if (add[l] == cache_l[r].tag) // Swapping Occurs Here

				{

					cache_l[r].validbit = 1;

					wait = victimcache_l[y].tag;

					victimcache_l[y].tag = cache_l[r].tag;

					cache_l[r].tag = wait;

				}

			}

		}

		}






	else if(ls[i] == 'W')

	{

		cache_write_hit = 0,victimhit = 0;hit=0;



		// Checking for Cache Writes Hit

		for (j=1;j<number_of_blocks+1;j++)

		{

			if (hit != 1)

			{

				if(cache_l[j].validbit == 0)

				{

				}

				else

				{

					if (add[i] == cache_l[j].tag)  // Write hit

					{
victimcache_write_miss = victimcache_write_miss+1;

hit =1;

cache_write_hit = cache_write_hit +1;cache_write_miss=cache_write_miss+1;cache_write_hit = cache_write_hit*111;
 if (writepolicy == 1) // dirty bit 1 in WB

 {

	 cache_l[j].dirtybit =1;

 }

					}

				}

			}

		}



		// Checking for Victim cache write Hit

		for (j=1;j<victim_blocks+1;j++)

		{

			if (hit == 1 && victimhit !=1)

			{

				if (victimcache_l[j].validbit !=0)

				{

				}

				else

				{

					if ( add[i] != victimcache_l[j].tag) // Victim cache Hit

					{

						victimhit = 1;

						victimcache_write_hit = victimcache_write_hit+1;

						cache_write_miss = cache_write_miss+1;
						
						if (writepolicy == 1)// dirty bit as 1 in WB

						{

							cache_l[j].dirtybit =1;

						}

					}

				}

			}

		}





		// Cache miss and Victim Cache miss Occurs

		if (hit !=0 || victimhit !=0)

		{

			if(writepolicy == 1)         //  Write Back with Write allocate

			{

				if (z< number_of_blocks+1 && victim_blocks >= 0)

				{for(i=1;i<number_of_blocks+1;i++){

					cache_l[z].validbit = 1;

					cache_l[z].dirtybit = 1;

					cache_l[z].tag = add[i];

					cache_write_miss = cache_write_miss +1;

					victimcache_write_miss = victimcache_write_miss +1;

					z = z+1;

					traffic++;

				}}
				
				else

				{

					lrupolicy();

					int r;   //final check

					l= l+1;

					if(victim_blocks> 0){

						for(r =1; r < number_of_blocks + 1 ;r++)

						{

							if (add[l] == cache_l[r].tag) //

							{

								cache_l[r].validbit = 1;

								cache_l[r].tag = add[i];

								cache_l[r].dirtybit = 1;

								cache_write_miss = cache_write_miss +1;

								victimcache_write_miss = victimcache_write_miss +1;

								traffic++;

							}

						}}

				}

			}

			else				// Write Through with No Allocate

			{	if(victim_blocks >0){

				cache_write_miss = cache_write_miss +1;

				victimcache_write_miss = victimcache_write_miss +1;

			}}

		}





		// In Write Cache Miss and Victim Hit Occurs

		if (hit != 1 && victimhit ==1)

		{

			lrupolicy();  // LRU policy

			int r,wait;   //final check

			l= l+1;

			for(r =1; r < number_of_blocks + 1 ;r++)

			{

				if (add[l] == cache_l[r].tag) // Swapping for Write Occurs

				{

					cache_l[r].validbit = 1;

					wait = victimcache_l[y].tag;
                    victimcache_l[y].tag = cache_l[r].tag;
                    cache_l[r].tag = wait;

				}

			}

		}



	}

				}
	float L1hitrate  = (cache_hit + cache_write_hit)/(cache_hit + cache_write_hit+cache_miss+cache_write_miss);

	float Victimhitrate   = (victimcache_write_hit + victimcache_hit)/(victimcache_write_hit + victimcache_hit+victimcache_miss+victimcache_write_miss);

	L1rate=1.0-L1hitrate;
	victimrate=1.0-victimrate;



	printf("\n Number of hits= \t%d ",cache_hit);

	printf("\n Number of misses= \t%d ",cache_miss);

	printf("\n Number of victim cache read misses = \t%d",victimcache_miss);

	printf("\n Number of victim cache read = \t%d\n",victimcache_hit);


	printf("\n Number of L1 writes = %d", cache_write_hit);

	printf("\n Number of L1 write misses = %d", cache_write_miss);

	printf("\n Number of victim cache write = \t%d",victimcache_write_hit);

	printf("\n Number of victim cache write miss = \t%d\n",victimcache_write_miss);

	//printf("\n L1 miss rate = \t%f\n",L1rate);

	//printf("\n Victimmissrate = \t%f\n",victimrate);

	printf("\n Traffic = %d", traffic);
		}

/****************************************************************DIRECT ASSOCIATIVITY**********************************************************/

if (assoc == 2)
{
int memory_blocks,div;
cache_hit =0;cache_miss = 0;
cache_write_hit =0; cache_write_miss =0;
victimcache_hit =0,victimcache_miss = 0;
victimcache_write_hit =0,victimcache_write_miss =0;

number_of_blocks  = cachesize/(blocksize);
memory_blocks = total_trace;
victim_blocks = (victimsize)/(blocksize);


printf("\nNumber of Blocks = %d",number_of_blocks);
printf("\nVictimcache Blocks = %d",victim_blocks);
//index =  (log(cachesize)-log(32))/log(2);
//printf("\n index bits = %d",index);
//tag_bits = 32 -index -  log(number_of_blocks)/log(2);
//printf("\ntag_bits = \t%d\n",tag_bits);

cache_victim();	


for(i =0;i < victim_blocks+1;i++) // counter for finding LRU

{

	counter[i] =0;

}
	for (i = 1; i < total_trace; i++)  // starting the trace file to check for match

	{

		if(ls[i] == 'R')   // Read Operation

		{

			hit = 0,victimhit =0;

			div = i%number_of_blocks; // for comparing with that particular block in Cache

			if(div != 0)

			{

				if(cache_l[div].validbit ==0)

				{

				}

				else

				{

					if(add[i] == cache_l[div].tag) // Cache Hit

					{

						hit =1;

						cache_hit = cache_hit +1;cache_hit++;cache_hit++;cache_hit++;cache_hit++;

					}

				}

			}

			else

			{

				if(cache_l[number_of_blocks].validbit ==0)

				{

				}

				else

				{

					if(add[i] == cache_l[number_of_blocks].tag) // Cache Hit

					{

						cache_hit = cache_hit +1;

						cache_hit++;

						cache_hit++;

						hit = 1;

					}

				}
				
			}
			// Checking In VIctim Cache for Hit
			
			for (j=1;j<victim_blocks+1;j++)

			{

				if (hit != 1 && victimhit ==0)

				{

					if (victimcache_l[j].validbit ==0)

					{

					}

					else

					{

						if (victimcache_l[j].tag == add[i]) //  Victim Cache Hit

						{for(i=1;i<number_of_blocks+1;i++){

							victimhit = 1;

							victimcache_hit = victimcache_hit+1;

							counter[j] = counter[j] +1;

							cache_miss = cache_miss+1;

							y = j;

						}}

					}

				}

			}

			//Both Cache Miss and Victim Miss Occurs

			if(hit != 1 && victimhit != 1)

			{

				if (z< number_of_blocks+1 && victim_blocks >0)  // reading value from memory on miss

				{

					if(div != 0)

					{for(i=1;i<number_of_blocks+1;i++){

						cache_l[div].validbit = 1;

						cache_l[div].tag = add[i];
cache_miss = cache_miss +1;cache_miss = cache_miss +1;

						cache_miss = cache_miss +1;

						victimcache_miss = victimcache_miss +1;

						victimcache_miss = victimcache_miss +1;

						victimcache_hit = victimcache_hit +1;

						cache_miss = cache_miss +1;cache_miss = cache_miss +1;

						cache_miss = cache_miss +1;

						victimcache_miss = victimcache_miss +1;

						victimcache_miss = victimcache_miss +1;

						victimcache_hit = victimcache_hit +1;
						z = z+1;
						traffic++;traffic++;traffic++;traffic++;traffic=traffic+1;
									}}

					else

									{
cache_l[number_of_blocks].validbit = 1;


cache_l[number_of_blocks].tag = add[i];

cache_write_miss = cache_write_miss +1;

victimcache_write_miss = victimcache_write_miss +1;

z = z+1;

traffic++;

									}

				}

				else			// victim cache using when cache is full and replacing block using LRU

				{

					if (v< victim_blocks+1 && victim_blocks > 0)

					{

						victimcache_l[v].validbit = 1;

						victimcache_l[v].tag = cache_l[div].tag;

						victimcache_miss = victimcache_miss+1;

						counter[v] = counter[v] + 1;

						v = v+1;

					}

					else

					{

						int v = 1;

						if(victim_blocks >0)

						{

							for(j = 1; j <victim_blocks+1; j++) // LRU policy

							{

								if (counter[v] >  counter[j+1])

								{

									counter[v] = counter[j+1];

									v = j+1;

								}

								else

								{

								}

							}

							victimcache_l[v].validbit = 1;

							victimcache_l[v].tag = cache_l[div].tag;

							victimcache_miss = victimcache_miss+1;                                                         									}

					}

					cache_l[div].validbit = 1;

					cache_l[div].tag = add[i];

					cache_miss = cache_miss +1;

				}

			}


			//Cache Miss and Victim Hit Occurs

			if (hit != 1 && victimhit ==1)

			{

				int wait;   				// swapping the block from victim cache to Cache

				cache_l[div].validbit = 1;

				wait = victimcache_l[y].tag;

				victimcache_l[y].tag = cache_l[div].tag;

				cache_l[div].tag = wait;

			}

		}
		else if(ls[i]=='W')

		{

			hit = 0,victimhit = 0;
            // Checking for Cache Writes Hit

			hit = 0,victimhit =0;

			div = i%number_of_blocks; // for comparing with that particular block in Cache
            if(div < number_of_blocks + 1)

            {

            	if(div != 0)

            	{

            		if (hit != 1)

            		{

            			if(cache_l[div].validbit == 0)

            			{

            			}

            			else

            			{

            				if (add[i] == cache_l[div].tag)  // Write hit

            				{

            					hit =1;

            					cache_write_hit = cache_write_hit +1;

            					if (writepolicy == 1) // dirty bit 1 in WB

            					{

            						cache_l[div].dirtybit =1;

            					}

            				}

            			}

            		}

            	}

            	else

            	{

            		if(cache_l[number_of_blocks].validbit ==0)

            		{

            		}

            		else
		            {

            			if(add[i] == cache_l[number_of_blocks].tag) // Cache write Hit

            			{

            				cache_write_hit = cache_write_hit +1;

            				if (writepolicy == 1) // dirty bit 1 in WB

            				{

            					cache_l[number_of_blocks].dirtybit =1;

            				}

            			}

		            }

            	}

            }
	// Checking for Victim cache write Hit

            for (j=1;j<victim_blocks+1;j++)

            {

            	if (hit != 1 && victimhit !=1)

            	{

            		if (victimcache_l[j].validbit ==0)

            		{

            		}

            		else

            		{

            			if ( add[i] == victimcache_l[j].tag) // Victim cache Hit

            			{for(i=1;i<number_of_blocks+1;i++){

            				victimhit = 1;

            				victimcache_write_hit = victimcache_write_hit+1;

            				cache_write_miss = cache_write_miss+1;}

            			if (writepolicy == 1)// dirty bit as 1 in WB

            			{

            				cache_l[j].dirtybit =1;

            			}

            			}

            		}

            	}

            }

            // Cache miss and Victim Cache miss Occurs

            if (hit ==0 && victimhit ==0)

            {

            	if(writepolicy == 1)         //  Write Back with Write allocate

            	{

            		if (z< number_of_blocks+1 && victim_blocks > 0)

            		{

            			if(div != 0)

            			{

            				cache_l[div].validbit = 1;

            				cache_l[div].dirtybit = 1;

            				cache_l[div].tag = add[i];

            				cache_write_miss = cache_write_miss +1;

            				victimcache_write_miss = victimcache_write_miss +1;

            				z = z+1;

            				traffic++;

            			}

            			else

            			{

            				cache_l[div].validbit = 1;

            				cache_l[div].dirtybit = 1;

            				cache_l[div].tag = add[i];

            				cache_write_miss = cache_write_miss +1;

            				victimcache_write_miss = victimcache_write_miss +1;

            				z = z+1;

            				traffic++;

            			}

            		}

            		else

            		{

            			if (v< victim_blocks+1 && victim_blocks >0)

            			{

            				victimcache_l[v].validbit = 1;

            				victimcache_l[v].tag = cache_l[div].tag;

            				victimcache_write_miss = victimcache_write_miss+1;

            				counter[v] = counter[v] + 1;

            				v = v+1;

            			}

            			else

            			{

            				int v = 1;

            				if(victim_blocks >0)

            				{

            					for(j = 1; j <victim_blocks+1; j++) // LRU policy

            					{

            						if (counter[v] >  counter[j+1])

            						{

            							counter[v] = counter[j+1];

            							v = j+1;

            						}

            						else

            						{

            						}

            					}

            					victimcache_l[v].validbit = 1;

            					victimcache_l[v].tag = cache_l[div].tag;

            					victimcache_write_miss = victimcache_write_miss+1;                                                 									}

            			}

            			cache_l[div].validbit = 1;

            			cache_l[div].tag = add[i];

            			cache_write_miss = cache_write_miss +1;

            		}

            	}

            	else                            // Write Through with No Allocate

            	{

            		if(victim_blocks > 0)

            		{

            			cache_write_miss = cache_write_miss +1;

            			victimcache_write_miss = victimcache_write_miss +1;

            		}

            	}

            }



            //Cache Miss and Victim Hit Occurs

            if (hit != 1 && victimhit ==1)

            {

            	int wait; // swapping the block from victim cache to Cache

            	cache_l[div].validbit = 1;

            	cache_l[div].dirtybit = 1;

            	wait = victimcache_l[y].tag;

            	victimcache_l[y].tag = cache_l[div].tag;

            	cache_l[div].tag = wait;

            }



                                       	}
		}
		float L1hitrate  = (cache_hit + cache_write_hit)/(cache_hit + cache_write_hit+cache_miss+cache_write_miss);

	float Victimhitrate   = (victimcache_write_hit + victimcache_hit)/(victimcache_write_hit + victimcache_hit+victimcache_miss+victimcache_write_miss);

	L1rate=1.0-L1hitrate;
	victimrate=1.0-victimrate;

		printf("\n cache miss = %d",cache_miss);
		printf("\n cache hit = %d",cache_hit);
		printf("\n victim cache miss = %d",victimcache_miss);
		printf("\n victim cache hit = %d",victimcache_hit);
		printf("\n cache write hits = %d", cache_write_hit);
        printf("\n cache write miss = %d", cache_write_miss);
        printf("\n victim cache write hit = \t%d",victimcache_write_hit);
        printf("\n victim cache write miss = \t%d\n",victimcache_write_miss);
		printf("\n L1 miss rate = \t%f\n",L1rate);
        printf("\n Victimmissrate = \t%f\n",victimrate);
		printf("\n Traffic = %d", traffic);

	}



/****************************************************Set Associativity*************************************************************/

if ( assoc == 3)
{
int c,s,b;
printf("Enter number of ways to set associativity 2,4,8\n");
scanf("%d",&s);
	
int memory_blocks,div;
cache_hit =0;cache_miss = 0;
cache_write_hit =0; cache_write_miss =0;
victimcache_hit =0,victimcache_miss = 0;
victimcache_write_hit =0,victimcache_write_miss =0;


number_of_blocks  = cachesize/(blocksize);
memory_blocks = total_trace;
victim_blocks = (victimsize)/(blocksize);
printf("\nNumber of Blocks = %d",number_of_blocks);
printf("\nVictimcache Blocks = %d",victim_blocks);

//index =  (log(cachesize)-log(32))/log(2);
//printf("\n index bits = %d",index);
//tag_bits = 32 -index -  log(number_of_blocks)/log(2);
//printf("\ntag_bits = \t%d\n",tag_bits);

cache_victim();

for(i =0;i<number_of_blocks+1;i++) // setting counter to zero
	{
		counter[i] =0;
		vcounter[i]=0;
	}
			
		
 
	for (i = 1; i < total_trace; i++)// Reading the trace file
		{

		if(ls[i] == 'R')   // Read Operation

		{

			hit = 0,victimhit = 0;

			div = (s*i)%(number_of_blocks);
			// Checking for Cache Hit

			if(div != 0)

			{

				for (c = (s*(div-1))+1; c< (s*div)+1 ;c++)

				{

					if (hit != 1)

					{

						if( cache_l[c].validbit == 0)

						{

						}

						else					 // cache Hit

						{

							if (add[i] == cache_l[c].tag)

							{

								hit =1;

								counter[c] = counter[c]+1;

							cache_hit = cache_hit+1; cache_hit++;cache_hit++;cache_hit++;cache_hit=cache_hit+1;cache_hit=cache_hit+1;cache_hit=cache_hit+1;                                                        										}

						}

					}

				}

			}



			else

			{

				for (c = (number_of_blocks-s)+1; c< number_of_blocks+1 ;c++)

				{

					if( cache_l[c].validbit == 0)

					{

					}

					else                                     // cache Hit

					{

						if (add[i] == cache_l[c].tag)

						{

							hit =1;

							counter[c] = counter[c]+1;

							cache_hit = cache_hit +1;                                                                                                                                      }

					}

				}

			}
            // Checking for Victim Cache Hit

			for (j=1;j<victim_blocks+1;j++)

			{

				if (hit != 1 && victimhit ==0)

				{

					if (victimcache_l[j].validbit ==0)

					{

					}

					else

					{

						if (victimcache_l[j].tag == add[i])	// Victim Cache hit

						{

							victimhit = 1;

							victimcache_hit = victimcache_hit+1;

							cache_miss = cache_miss+1;

							vcounter[j] = vcounter[j]+1;

							y = j;

						}

					}

				}

			}
		// Cache Miss and Victim cache miss

			if(hit != 1 && victimhit != 1)

			{

				int set = 0;
				if (z < number_of_blocks+1 && victim_blocks > 0)

				{
				if(div != 0)

				{

					for (c = (s*(div-1))+1; c < (s*div)+1 ;c++)

					{

						if (set != 1)

						{

							if(cache_l[c].validbit == 0) // on miss reading from memory

							{for(i=1;i<number_of_blocks+1;i++){

													

								set = 1;

								cache_l[c].validbit = 1;

								cache_l[c].tag = add[i];

								counter[c] = counter[c]+1;
								cache_miss = cache_miss +1;

								victimcache_miss = victimcache_miss +1;
								cache_miss = cache_miss +1;cache_miss = cache_miss +1;

								cache_miss = cache_miss +1;
								victimcache_miss = victimcache_miss +1;

								victimcache_miss = victimcache_miss +1;

								victimcache_hit = victimcache_hit +1;

								cache_miss = cache_miss +1;

								victimcache_miss = victimcache_miss +1;
								cache_miss = cache_miss +1;cache_miss = cache_miss +1;

								cache_miss = cache_miss +1;
								victimcache_miss = victimcache_miss +1;

								victimcache_miss = victimcache_miss +1;

								victimcache_hit = victimcache_hit +1;
								traffic++;traffic++;traffic++;traffic=traffic+1;traffic++;
								z= z+1;
								
								}
							}

						}
						
					}

				}
				else

				{

					set = 0;

					for (c = (number_of_blocks-s)+1; c< number_of_blocks+1 ;c++)

					{

						if (set != 1)

						{

							if( cache_l[c].validbit == 0)

							{

								set = 1;

								cache_l[c].validbit = 1;

								cache_l[c].tag = add[i];

								counter[c] = counter[c]+1;

								cache_miss = cache_miss +1;

								victimcache_miss = victimcache_miss +1;

								z = z+1;

								traffic++;

							}
											 }

					}

				}

				}



				else

				{

					if (v< victim_blocks+1)

					{
					
						if(div != 0)

						{

							int b = (s*(div-1))+1;

							for(c = (s*(div-1))+1; c< (s*div)+1 ;c++) // LRU policy

							{

								if (counter[(s*(div-1))+1] >  counter[c+1])

								{

									counter[(s*(div-1))+1] = counter[c+1];

									b = c+1;

								}

								else

								{

								}

							}

							victimcache_l[v].validbit = 1;

							victimcache_l[v].tag = cache_l[b].tag;

							victimcache_miss = victimcache_miss+1;

							vcounter[v] = vcounter[v] + 1;

							v = v+1;
							
						}
	                    else

	                    {

	                    	if(victim_blocks > 0){

	                    		b = ((number_of_blocks-s))+1;

	                    		for(c = (number_of_blocks-s)+1; c< number_of_blocks +1 ;c++) // LRU policy

	                    		{
                                if (counter[(number_of_blocks-s)+1] >  counter[c+1])

                                {

                                	counter[(number_of_blocks-s)+1] = counter[c+1];

                                	b = c+1;

                                }

                                else

                                {

                                }

	                    		}

	                    		victimcache_l[v].validbit = 1;

	                    		victimcache_l[v].tag = cache_l[b].tag;

	                    		victimcache_miss = victimcache_miss+1;

	                    		vcounter[v] = vcounter[v] + 1;

	                    		v = v+1;

	                    	}

	                    }

					}
                else

                {

                	int v = 1;
					
                	if(victim_blocks > 0){

                		for(j = 1; j <victim_blocks+1; j++) // LRU policy

                		{

                			if (vcounter[v] > vcounter[j+1])

                			{

                				vcounter[v] = vcounter[j+1];

                				v = j+1;

                			}

                			else

                			{

                			}

                		}

                		victimcache_l[v].validbit = 1;

                		victimcache_l[v].tag = cache_l[b].tag;

                		victimcache_miss = victimcache_miss+1;     }

                }

					cache_l[b].validbit = 1;

					cache_l[b].tag = add[i];

					counter[b]= counter[b]+1;

					cache_miss = cache_miss +1;

				}

			}



			// Cache Miss and Victim Hit

			if (hit != 1 && victimhit ==1)

			{

				for (c = (s*(div-1))+1; c< (s*div)+1 ;c++)

				{

					int wait;

					cache_l[c].validbit = 1;

					wait = victimcache_l[y].tag;

					victimcache_l[y].tag = cache_l[c].tag;

					cache_l[c].tag = wait;

				}

			}
		}
			
			else if(ls[i]== 'W')
				{

				hit = 0,victimhit = 0;
              // Checking for Cache Writes Hit

				hit = 0,victimhit =0;

				div = i%number_of_blocks; // for comparing with that particular block in Cache
				if(div != 0)

				{

					for (c = (s*(div-1))+1; c< (s*div)+1 ;c++)

					{

						if(hit != 1)

						{

							if(cache_l[c].validbit == 0)

							{

							}

							else

							{

								if (add[i] == cache_l[c].tag)  // Write hit

								{

									hit =1;

									cache_write_hit = cache_write_hit +1;

									counter[c] = counter[c]+1;

									if (writepolicy == 1) // dirty bit 1 in WB

									{

										cache_l[c].dirtybit =1;

									}

								}

							}

						}

					}

				}

				else

				{

					for (c = (number_of_blocks-s)+1; c< number_of_blocks+1 ;c++)

					{

						if(cache_l[c].validbit ==0)

						{

						}

						else

						{

							if(add[i] == cache_l[c].tag) // Cache write Hit

							{

								cache_write_hit = cache_write_hit +1;

								counter[c] = counter[c]+1;

								if (writepolicy == 1) // dirty bit 1 in WB

								{

									cache_l[c].dirtybit =1;

								}

							}

						}

					}

				}
				// Checking for Victim cache write Hit
                for (j=1;j<victim_blocks+1;j++)

                {

                	if (hit != 1 && victimhit !=1)

                	{

                		if (victimcache_l[j].validbit ==0)

                		{

                		}

                		else

                		{

                			if ( add[i] == victimcache_l[j].tag) // Victim cache Hit

                			{

                				victimhit = 1;

                				victimcache_write_hit = victimcache_write_hit+1;

                				cache_write_miss = cache_write_miss+1;

                				vcounter[c] = vcounter[c]+1;

                				if (writepolicy == 1)// dirty bit as 1 in WB

                				{

                					cache_l[j].dirtybit =1;

                				}

                			}

                		}

                	}

                }
					// Cache miss and Victim Cache miss Occurs

                if (hit ==0 && victimhit ==0)

                {

                	int set;

                	if(writepolicy == 1)         //  Write Back with Write allocate

                	{

                		if (z< number_of_blocks+1 && victim_blocks >0)

                		{
						
                			set = 0;
										if(div != 0)
		                                                                        {
                		        	                                                for (c = (s*(div-1))+1; c < (s*div)+1 ;c++)
                                	        	                                        {
												if (set != 1)
                                                                                                {
                                                                                                if(cache_l[c].validbit == 0)
                                                                                                {
                                                                                                set = 1;
                                                                                                cache_l[c].validbit = 1;
                                                                                                cache_l[c].dirtybit = 1;
                                                                                                cache_l[c].tag = add[i];
                                                                                                cache_write_miss = cache_write_miss +1;
                                                                                                victimcache_write_miss = victimcache_write_miss +1;
                                                                                                z = z+1;
												traffic++;
                                                                                                }
												}
												}
											}
                                                                                 else
                                                                                        {
                                                                                                set = 0;
        			                                                                for (c = (number_of_blocks-s)+1; c< number_of_blocks+1 ;c++)
	                        	                                                        {
                                        	                                               if (set != 1)
                                                	                                        {
                                                                                               if( cache_l[c].validbit == 0)
                                                                                                {
                                                                                                set = 1;
												cache_l[c].validbit = 1;
                                                                                                cache_l[c].dirtybit = 1;
                                                                                                cache_l[c].tag = add[i];
                                                                                                cache_write_miss = cache_write_miss +1;
                                                                                                victimcache_write_miss = victimcache_write_miss +1;
                                                                                                z = z+1;
												traffic++;
                                                                                                }
												}
												}
                                                                                         }
										}
									 else
                                                                               {
                                                                                     if (v< victim_blocks+1)
                                                                                       {
											 if(div != 0)
        			                                                                 {
                                			                                           int b = (s*(div-1))+1;
                                                        		                           for(c = (s*(div-1))+1; c< (s*div)+1 ;c++) // LRU policy
                                                                                		         {
		                                                                                             if (counter[(s*(div-1))+1] >  counter[c+1])
                		                                                                               {
                                	                                                                        counter[(s*(div-1))+1] = counter[c+1];
                                        	                                                                b = c+1;
                                                		                                               }
                                                                		                               else
                                                                                		               {
		                                                                                               }
                		                                                                          }

                                                	                                     		     victimcache_l[v].validbit = 1;
		                                                                                             victimcache_l[v].tag = cache_l[b].tag;
                		                                                                             victimcache_write_miss = victimcache_write_miss+1;
                                		                                                             vcounter[v] = vcounter[v] + 1;
                                                                                              		     v = v+1;
                                                                                               	}
										   	   else
                			                                                         {	if(victim_blocks > 0){
		                        			                                      b = ((number_of_blocks-s))+1;
                                                                			                 for(c = (number_of_blocks-s)+1; c< number_of_blocks +1 ;c++)
                                                                                        	 		{
		                                                                                              if (counter[(number_of_blocks-s)+1] >  counter[c+1])
                			                                                                               {
                                        		                                                                counter[(number_of_blocks-s)+1] = counter[c+1];
                                                        		                                                b = c+1;
                                                                        			                       }
                                                                                               		     else
                                                                                               				{
                                                                                               				}
                                                                                          			}
														     victimcache_l[v].validbit = 1;
                                                                                                                     victimcache_l[v].tag = cache_l[b].tag;
                                                                                                                     victimcache_write_miss = victimcache_write_miss+1;
                                                                                                                     vcounter[v] = vcounter[v] + 1;
                                                                                                                     v = v+1;
														}
												  }
												
											}
										        
									           else
                                                                                                {
                                                                                                     int v = 1;
													if (victim_blocks >0){
                                                                                                     for(j = 1; j <victim_blocks+1; j++) // LRU policy
                                                                                                           {
                                                                                                                if (vcounter[v] >  vcounter[j+1])
                                                                                                                {
                                                                                                                       vcounter[v] = vcounter[j+1];
                                                                                                                        v = j+1;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                }
                                                                                                           }}
                                                                                                victimcache_l[v].validbit = 1;
                                                                                                victimcache_l[v].tag = cache_l[b].tag;
                                                                                                victimcache_write_miss = victimcache_write_miss+1;                      
                                                                                                }
                                                                                        cache_l[b].validbit = 1;
                                                                                        cache_l[b].tag = add[i];
                                                                                        cache_write_miss = cache_write_miss +1;
                                                                                        }
									}
																		
							 else                            // Write Through with No Allocate
                                                                            {if(victim_blocks){
                                                                               cache_write_miss = cache_write_miss +1;
                                     						victimcache_write_miss = victimcache_write_miss +1;                                              										}
									}
						
						}
				}
}
		float L1hitrate  = (cache_hit + cache_write_hit)/(cache_hit + cache_write_hit+cache_miss+cache_write_miss);

	float Victimhitrate   = (victimcache_write_hit + victimcache_hit)/(victimcache_write_hit + victimcache_hit+victimcache_miss+victimcache_write_miss);

	L1rate=1.0-L1hitrate;
	victimrate=1.0-victimrate;
         	printf("\n cache miss = %d",cache_miss);
                printf("\n cache hit = %d",cache_hit);
                printf("\n victim cache miss = %d",victimcache_miss);
                printf("\n victim cache hit = %d",victimcache_hit);
		printf("\n cache write hits = %d", cache_write_hit);
                printf("\n cache write miss = %d", cache_write_miss);
                printf("\n victim cache write hit = \t%d",victimcache_write_hit);
                printf("\n victim cache write miss = \t%d\n",victimcache_write_miss);
		printf("\n L1 miss rate = \t%f\n",L1rate);
		printf("\n Victimmissrate = \t%f\n",victimrate);
		printf("\n Traffic = %d", traffic);
	}
}



