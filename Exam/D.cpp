/********************************************************************
** Exam - D - Floyd
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

const int MAX_VERTEX_NUM = 128;

const long long INF = 0x3f3f3f3f3f3f3f3f;

long long dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

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
	int n, m, k;
	int u, v, w;
	int q;

	memset(dist, 0x3f, sizeof(dist));

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		dist[i][i] = 0;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		dist[u][v] = std::min(dist[u][v], (long long)w);
		dist[v][u] = std::min(dist[v][u], (long long)w);
	}

	// Floyed
	for (int t = 1; t <= n; t++)
	{
		if (t > k)
			continue;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				dist[i][j] = std::min(dist[i][j], dist[i][t] + dist[t][j]);
		}
	}

	scanf("%d", &q);
	while (q--)
	{
		scanf("%d %d", &u, &v);
		if (dist[u][v] != INF)
			printf("%lld\n", dist[u][v]);
		else
			printf("QAQ\n");
	}
}

