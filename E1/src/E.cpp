/********************************************************************
** E1 - E
*/

#include <cstdio>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

long long UPPER_BOUND = 1000000009LL;

int main()
{
	int t;
	int m, n;
	long long ans;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);

		ans = 1LL;
		long long nume = n - m + 1;
		for (int i = 1; i <= m; i++)
		{
			ans = ans * nume / i;
			nume++;
			if (ans > UPPER_BOUND)
			{
				ans = -1;
				break;
			}
		}

		printf("%lld\n", ans);
	}

	return 0;
}
