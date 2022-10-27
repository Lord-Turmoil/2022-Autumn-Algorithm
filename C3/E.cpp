/********************************************************************
** C3 - E
*/

#include <cstdio>
#include <climits>
#include <functional>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_SIZE = 1001;

int matrix[MAX_SIZE][MAX_SIZE];
long long dp[MAX_SIZE][MAX_SIZE];
int n, m;

long long solve();
int main()
{
	int t;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				scanf("%d", &matrix[i][j]);
				// Initialize by the way.
				dp[i][j] = LLONG_MIN;
			}
		}

		printf("%lld\n", solve());
	}

	return 0;
}

long long solve()
{
	dp[1][1] = (long long)matrix[1][1];
	for (int i = 2; i <= n; i++)
		dp[i][1] = dp[i - 1][1] + (long long)matrix[i][1];
	for (int i = 2; i <= m; i++)
		dp[1][i] = dp[1][i - 1] + (long long)matrix[1][i];

	for (int i = 2; i <= n; i++)
	{
		for (int j = 2; j <= m; j++)
			dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + (long long)matrix[i][j];
	}

#ifdef INTERNAL
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			printf("%10d ", dp[i][j]);
		putchar('\n');
	}
#endif

	return dp[n][m];
}
