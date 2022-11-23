/********************************************************************
** E5 - E
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>
#include <queue>

const int MOD = 998244353;
const int MAX_VERTEX_NUM = 1000004;
const int MAX_EDGE_NUM = 1600004;

std::vector<int> matrix[MAX_VERTEX_NUM];
int depth[MAX_VERTEX_NUM];
bool visited[MAX_VERTEX_NUM];
int cnt[MAX_VERTEX_NUM];

int main()
{
	int n, m;
	int src, dest;

	scanf("%d %d %d %d", &n, &m, &src, &dest);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		if (u != v)
		{
			matrix[u].push_back(v);
			matrix[v].push_back(u);
		}
	}

	std::queue<int> candidates;
	depth[src] = 0;
	visited[src] = true;
	cnt[src] = 1;
	candidates.push(src);
	while (!candidates.empty())
	{
		int u = candidates.front();
		candidates.pop();
		for (auto v : matrix[u])
		{
			if (!visited[v])
			{
				visited[v] = true;
				depth[v] = depth[u] + 1;
				candidates.push(v);
			}
			if (depth[v] == depth[u] + 1)
			{
				cnt[v] = (cnt[u] + cnt[v]) % MOD;
			}
		}
	}
	printf("%d\n", cnt[dest]);

	return 0;
}
