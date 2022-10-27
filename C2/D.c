/********************************************************************
** C2 - D TLE
*/
#include <stdio.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define MAX_N 10000086

unsigned seed;
unsigned Rand(void)
{
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	return seed;
}


inline unsigned MaxInt(int a, int b)
{
	return (a > b) ? a : b;
}

inline unsigned MaxUnsigned(unsigned a, unsigned b)
{
	return (a > b) ? a : b;
}

unsigned findMax(int left, int right);

unsigned a[MAX_N];
int main(void)
{
	int t, n, k;
	unsigned ans;

	scanf("%d", &t);
	while (t--)
	{
		ans = 0;
		scanf("%d %d %u", &n, &k, &seed);
		for (int i = 1; i <= n; i++)
		{
			a[i] = Rand();
			ans += findMax(MaxInt(1, i - k + 1), i + 1) ^ i;
		}

		printf("%u\n", ans);
	}
}

/********************************************************************
** [left, right)
*/
unsigned findMax(int left, int right)
{
	if (right == left + 1)	// only one element
		return a[left];
	else if (right == left + 2)		// two elements
		return MaxUnsigned(a[left], a[left + 1]);

	int mid = left + ((right - left) >> 1);

	return MaxUnsigned(findMax(left, mid), findMax(mid, right));
}
