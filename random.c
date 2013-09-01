#include <stdlib.h>
#include <stdio.h>


// http://www.xkcd.com/221/

// Internal helpers:

// __attribute__((visibility("internal")))
static long int __my_random()
{
	static long int * ret = NULL;
        if (!ret) {
                char *num = getenv("GUARANTEED_RANDOM");
		ret = malloc(sizeof(long int));
		if (num) {
			*ret = atol(num);
		} else {
			*ret = 0;
		}
	}
	return *ret;
}

// Overrides:

__attribute__((visibility("default")))
long int random(void)
{
	return __my_random();
}

__attribute__((visibility("default")))
void srandom(unsigned int seed)
{
	fprintf(stderr, "Ignoring random seed: %u\n", seed);
}
