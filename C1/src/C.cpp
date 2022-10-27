/*
** C
*/
#include <cstdio>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 100005;
const long long MOD = 1000000006;

long long arr[SIZE];
long long left[SIZE];
long long right[SIZE];
int main()
{
	int t;
	int n;
	long long product;

	scanf("%d", &t);
	while (t--)
	{
		product = 1LL;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lld", &arr[i]);
		
		left[0] = 1;
		for (int i = 1; i < n; i++)
			left[i] = (left[i - 1] * (arr[i - 1] % MOD)) % MOD;
		right[n - 1] = 1;
		for (int i = n - 2; i >= 0; i--)
			right[i] = (right[i + 1] * (arr[i + 1] % MOD)) % MOD;
		
#ifdef INTERNAL
		for (int i = 0; i < n; i++)
			printf("\t %lld\t %lld\n", left[i], right[i]);
#endif

		for (int i = 0; i < n; i++)
			printf("%lld ", (left[i] * right[i]) % MOD);
		putchar('\n');
	}
	return 0;
}

