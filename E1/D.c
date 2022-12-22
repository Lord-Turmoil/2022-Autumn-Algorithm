/********************************************************************
** C1 - D
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define SIZE		20000010
#define UPPER_BOUND (1u << 24)

unsigned seed;

unsigned Rand(void)
{
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	return seed & ((1 << 24) - 1);
}

int comp(const void* a, const void* b)
{
	return *((int*)a) - *((int*)b);
}

unsigned bucket[UPPER_BOUND + 4];
int main(void)
{
	int t;
	int n;

	scanf("%d", &t);

	while (t--)
	{
		scanf("%d %u", &n, &seed);

		for (int i = 0; i < n; i++)
			bucket[Rand()]++;

		unsigned ans = 0;
		unsigned cnt = 1;
		for (unsigned i = 0; i < UPPER_BOUND; i++)
		{
			while (bucket[i] != 0)
			{
				ans += i ^ cnt;
				bucket[i]--;
				cnt++;
			}
		}

		printf("%u\n", ans);
	}

	return 0;
}
