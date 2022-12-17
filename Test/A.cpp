/********************************************************************
** Test - A
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <stdio.h>

long long sum(int base, int delta, int day);
int main()
{
	int n, m, k;

	while (scanf("%d %d %d", &n, &m, &k) != EOF)
	{
		k++;
		printf("%lld\n", sum(n, m, k));
	}

	return 0;
}

long long sum(int base, int delta, int day)
{
	long long ret = 1LL * base * day;

	ret += (0LL + 1LL * delta * (day - 1)) * day / 2LL;

	return ret;
}
