/********************************************************************
** C3 - B
*/

#include <cstdio>
#include <cstring>
#include <climits>
#include <functional>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_SIZE = 304;

long long dp[MAX_SIZE][MAX_SIZE];
long long a[MAX_SIZE];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
		scanf("%lld", &a[i]);

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
			dp[i][j] = LLONG_MAX;
	}

	for (int i = 1; i <= n; i++)
		dp[i][i] = 0;

	for (int length = 2; length <= n; length++)
	{
		int upper = n - length + 1;
		for (int i = 1; i <= upper; i++)
		{
			int j = i + length - 1;

			// i   k   j
			// A A A A A
			// (Ai...Ak)(Ak+1...Aj)
			for (int k = i; k < j; k++)
				dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j] + a[i - 1] * a[k] * a[j]);
		}
	}

#ifdef INTERNAL
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%15lld ", dp[i][j]);
		putchar('\n');
	}
#endif

	printf("%lld\n", dp[1][n]);

	return 0;
}
