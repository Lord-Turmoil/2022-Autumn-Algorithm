/********************************************************************
** E4 - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

const int MAX_VERTEX_NUM = 200004;
const int MAX_EDGE_NUM = 500004;

const long long INF = 0x1f1f1f1f1f1f1f1f;

struct Edge
{
	int v;
	int w;
	int next;
};

Edge edge[MAX_EDGE_NUM << 1];
int dist[MAX_VERTEX_NUM];
int head[MAX_VERTEX_NUM];
bool flag[MAX_VERTEX_NUM];
int edgestamp;

void _addSingleEdge(int u, int v, int w) {
	edgestamp++;
	edge[edgestamp].v = v;
	edge[edgestamp].w = w;
	edge[edgestamp].next = head[u];
	head[u] = edgestamp;
}

void addEdge(int u, int v, int w)
{
	if (u != v)
	{
		_addSingleEdge(u, v, w);
		_addSingleEdge(v, u, w);
	}
}

long long prim(int src, int vertexNum);
int main()
{
	int n, m;
	int u, v, w;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}

	printf("%lld\n", prim(1, n));

	return 0;
}

long long prim(int src, int vertexNum)
{
	std::priority_queue<
		std::pair<int, int>,
		std::vector<std::pair<int, int>>,
		std::greater<std::pair<int, int>>> heap;
	long long ret = 0;
	int cnt = 0;	// just the src
	int u, v, w;

	memset(dist + 1, 0x7F, sizeof(int) * vertexNum);
	dist[src] = 0;
	heap.push(std::make_pair(dist[src], src));
	while (!heap.empty())
	{
		u = heap.top().second;
		w = heap.top().first;
		heap.pop();

		if (flag[u])
			continue;
		flag[u] = true;
		ret += (long long)w;
		cnt++;
		if (cnt == vertexNum)
			break;

		for (int i = head[u]; i != 0; i = edge[i].next)
		{
			v = edge[i].v;
			w = edge[i].w;
			if (dist[v] > w)
			{
				dist[v] = w;
				heap.push(std::make_pair(dist[v], v));
			}
		}
	}

	return ret;
}

