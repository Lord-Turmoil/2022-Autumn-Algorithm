/********************************************************************
** E4 - A
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int MAX_VERTEX_NUM = 512;

long long dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
int main()
{
	int n, m, q;
	int u, v, w;
	long long infinite;

	memset(dist, 0x1f, sizeof(dist));
	infinite = dist[0][0];

	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= n; i++)
		dist[i][i] = 0;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		dist[u][v] = std::min(dist[u][v], (long long)w);
	}

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
		}
	}

	while (q--)
	{
		scanf("%d %d", &u, &v);
		if (dist[u][v] != infinite)
			printf("%lld\n", dist[u][v]);
		else
			printf("No So1ution\n");
	}

	return 0;
}
