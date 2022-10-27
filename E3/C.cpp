/********************************************************************
** E3 - C
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <climits>
#include <algorithm>

const int MAX_N = 512;

// if i < j, then dp[i][j] = sum[i][j] = 0
int dp[MAX_N][MAX_N];
int sum[MAX_N][MAX_N];
int cost[MAX_N];
int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &cost[i]);

	// pre-process
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			dp[i][j] = (i == j) ? cost[i] : INT_MAX;
			for (int k = i; k <= j; k++)
				sum[i][j] = sum[i][j - 1] + cost[k];
		}
		
	}

#ifdef INTERNAL
	printf("===== SUM =====\n");
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%5d ", sum[i][j]);
		putchar('\n');
	}
	printf("===============\n");
#endif

	for (int length = 2; length <= n; length++)
	{
		int upper = n - length + 1;
		for (int i = 1; i <= upper; i++)
		{
			int j = i + length - 1;
			for (int k = i; k <= j; k++)
			{
				if (k == i)
					dp[i][j] = std::min(dp[i][j], dp[k + 1][j] + sum[k + 1][j] + cost[k]);
				else if (k == j)
					dp[i][j] = std::min(dp[i][j], dp[i][k - 1] + sum[i][k - 1] + cost[k]);
				else
				{
					dp[i][j] = std::min(
						dp[i][j],
						dp[i][k - 1] + sum[i][k - 1] + dp[k + 1][j] + sum[k + 1][j] + cost[k]);
				}
			}
		}
	}

#ifdef INTERNAL
	printf("===== DP =====\n");
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%5d ", dp[i][j]);
		putchar('\n');
	}
	printf("==============\n");
#endif

	printf("%d\n", dp[1][n]);

	return 0;
}
