/********************************************************************
** C3 - E
*/

#include <cstdio>
#include <cstring>
#include <stack>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_SIZE = 128;
const int MAX_LINE_NUM = 16;

int assem_cost[MAX_LINE_NUM][MAX_SIZE];
int trans_cost[MAX_LINE_NUM][MAX_LINE_NUM];
int trace[MAX_LINE_NUM][MAX_SIZE];

// dp[i][j]: lowest cost until work station j of line i.
int dp[MAX_LINE_NUM][MAX_SIZE];

void solve();
int main()
{
	int t;

	scanf("%d", &t);
	while (t--)
		solve();

	return 0;
}

void solve()
{
	// n: line num
	// m: line size
	int n, m;

	// Readin.
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			scanf("%d", &assem_cost[i][j]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			scanf("%d", &trans_cost[i][j]);
	}

	// Find lowest cost.
	for (int i = 1; i <= n; i++)
		dp[i][1] = assem_cost[i][1];
	// s is current station id
	for (int s = 2; s <= m; s++)
	{
		// i: current line
		// j: other line
		for (int i = 1; i <= n; i++)
		{
			int self_cost = dp[i][s - 1] + trans_cost[i][i];
			int other_cost;
			int min_cost = self_cost;
			int candidate = i;
			for (int j = 1; j <= n; j++)
			{
				if (j == i)
					continue;
				other_cost = dp[j][s - 1] + trans_cost[j][i];
				if (other_cost < min_cost)
				{
					min_cost = other_cost;
					candidate = j;
				}
			}
			dp[i][s] = min_cost + assem_cost[i][s];
			trace[i][s] = candidate;
		}
	}

	// Find best solution.
	int cost;
	int line = 1;
	int min_cost = dp[1][m];
	std::stack<int> path;

	for (int i = 2; i <= n; i++)
	{
		if (dp[i][m] < min_cost)
		{
			min_cost = dp[i][m];
			line = i;
		}
	}
	cost = dp[line][m];

	path.push(line);
	for (int i = m; i > 1; i--)
	{
		path.push(trace[line][i]);
		line = trace[line][i];
	}

	printf("%d\n", cost);
	while (!path.empty())
	{
		printf("%d\n", path.top());
		path.pop();
	}
}

