/********************************************************************
** C5 - A
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>

const int MAX_VERTEX_NUM = 302;
const int INF = 0x3f3f3f3f;

int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int main()
{
	int t;
	int n, m;
	int u, v, w;
	int target, cnt;
	std::vector<std::pair<int, int>> result;

	result.resize(MAX_VERTEX_NUM * MAX_VERTEX_NUM);

	scanf("%d", &t);
	while (t--)
	{
		memset(dist, 0x3f, sizeof(dist));

		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			dist[i][i] = 0;
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &u, &v, &w);
			dist[u][v] = dist[v][u] = w;
		}

		for (int k = 1; k <= n; k++)
		{
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
					dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}

		target = 0;
		cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (dist[i][j] == INF)
					continue;
				if (dist[i][j] > target)
				{
					target = dist[i][j];
					cnt = 1;
					result[0] = std::make_pair(i, j);
				}
				else if (dist[i][j] == target)
				{
					result[cnt] = std::make_pair(i, j);
					cnt++;
				}
			}
		}

		printf("%d %d\n", target, cnt);
		for (int i = 0; i < cnt; i++)
			printf("%d %d\n", result[i].first, result[i].second);
	}

	return 0;
}
