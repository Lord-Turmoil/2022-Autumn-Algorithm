/********************************************************************
** C3 - C
*/

#include <cstdio>
#include <cstring>
#include <stack>

#ifdef INTERNAL
#include <assert.h>
#pragma warning(disable: 4996)
#endif

const int MAX_SIZE = 128;

int assem_cost[2][MAX_SIZE];
int trans_cost[2][2];
int trace[2][MAX_SIZE];

// dp[i][j]: lowest cost until work station j of line i.
int dp[2][MAX_SIZE];

int main()
{
	int n;

	// Readin.
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &assem_cost[0][i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &assem_cost[1][i]);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			scanf("%d", &trans_cost[i][j]);
	}

	// Find lowest cost.
	dp[0][1] = assem_cost[0][1];
	dp[1][1] = assem_cost[1][1];
	for (int i = 2; i <= n; i++)
	{
		// line 0
		if (dp[0][i - 1] + trans_cost[0][0] < dp[1][i - 1] + trans_cost[1][0])
		{
			trace[0][i] = 0;
			dp[0][i] = dp[0][i - 1] + trans_cost[0][0] + assem_cost[0][i];
		}
		else
		{
			trace[0][i] = 1;
			dp[0][i] = dp[1][i - 1] + trans_cost[1][0] + assem_cost[0][i];
		}

		// line 1
		if (dp[1][i - 1] + trans_cost[1][1] < dp[0][i - 1] + trans_cost[0][1])
		{
			trace[1][i] = 1;
			dp[1][i] = dp[1][i - 1] + trans_cost[1][1] + assem_cost[1][i];
		}
		else
		{
			trace[1][i] = 0;
			dp[1][i] = dp[0][i - 1] + trans_cost[0][1] + assem_cost[1][i];
		}
	}

	// Find best solution.
	int cost;
	int line;
	std::stack<int> path;

	line = (dp[0][n] < dp[1][n]) ? 0 : 1;
	cost = dp[line][n];

	path.push(line + 1);
	for (int i = n; i > 1; i--)
	{
		path.push(trace[line][i] + 1);
		line = trace[line][i];
	}

#ifdef INTERNAL
	assert(path.size() == n);
#endif

	printf("%d\n", cost);
	for (int i = 1; i <= n; i++)
	{
		printf("Station%d, Line%d\n", i, path.top());
		path.pop();
	}

	return 0;
}
