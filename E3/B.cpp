/********************************************************************
** E3 - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

const int MAX_LENGTH = 1024;

enum class Direction
{
	TOP,
	LEFT,
	DIAGONAL
};

char patternA[MAX_LENGTH];
char patternB[MAX_LENGTH];

int dp[2][MAX_LENGTH];
Direction path[MAX_LENGTH][MAX_LENGTH];
int main()
{
	int n;	// length A
	int m;	// length B
	int pre, cur;

	scanf("%s", patternA + 1);
	scanf("%s", patternB + 1);
	n = strlen(patternA + 1);
	m = strlen(patternB + 1);

	pre = 0;
	cur = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (patternA[i] == patternB[j])
			{
				dp[cur][j] = dp[pre][j - 1] + 1;
				path[i][j] = Direction::DIAGONAL;
			}
			else
			{
				if (dp[cur][j - 1] >= dp[pre][j])
				{
					dp[cur][j] = dp[cur][j - 1];
					path[i][j] = Direction::LEFT;
				}
				else
				{
					dp[cur][j] = dp[pre][j];
					path[i][j] = Direction::TOP;
				}
			}
		}
		std::swap(cur, pre);
	}

	int ans = dp[pre][m];
	std::stack<int> result;
	int x = n;
	int y = m;

	while ((x != 0) && (y != 0))
	{
		switch (path[x][y])
		{
		case Direction::TOP:
			x--;
			break;
		case Direction::LEFT:
			y--;
			break;
		case Direction::DIAGONAL:
			result.push(x);
			x--;
			y--;
			break;
		default:
			break;
		}
	}

#ifdef INTERNAL
	printf("%d\n", ans);
#endif

	while (!result.empty())
	{
		printf("%c", patternA[result.top()]);
		result.pop();
	}
	putchar('\n');

	return 0;
}
