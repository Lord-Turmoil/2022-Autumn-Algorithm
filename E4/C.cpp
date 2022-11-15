/********************************************************************
** E4 - C
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <queue>

const int MAX_VERTEX_NUM	= 1000004;
const int MAX_EDGE_NUM		= 1600004;

struct Edge
{
	int v;
	int w;
	int next;
};

int			head[MAX_VERTEX_NUM];
Edge		edge[MAX_EDGE_NUM * 2];
bool		flag[MAX_VERTEX_NUM];
long long	dist[MAX_VERTEX_NUM];
int			edgestamp;

void addEdge(int u, int v, int w);
void _addSingleEdge(int u, int v, int w);
long long dijkstra(int src, int dest);

int main()
{
	int n, m;
	int src, dest;
	int u, v, w;

	scanf("%d %d %d %d", &n, &m, &src, &dest);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}

	printf("%lld\n", dijkstra(src, dest));

	return 0;
}

void addEdge(int u, int v, int w)
{
	if (u != v)
	{
		_addSingleEdge(u, v, w);
		_addSingleEdge(v, u, w);
	}
}

void _addSingleEdge(int u, int v, int w)
{
	edgestamp++;
	edge[edgestamp].next = head[u];
	edge[edgestamp].v = v;
	edge[edgestamp].w = w;
	head[u] = edgestamp;
}

long long dijkstra(int src, int dest)
{
	std::priority_queue<
		std::pair<long long, int>,
		std::vector<std::pair<long long, int>>,
		std::greater<std::pair<long long, int>>> heap;
	int u, v, w;

	memset(dist, 0x3f, sizeof(dist));
	dist[src] = 0LL;
	heap.push(std::make_pair(dist[src], src));
	while (!heap.empty())
	{
		u = heap.top().second;
		heap.pop();

		if (flag[u])
			continue;
		flag[u] = true;

		for (int i = head[u]; i != 0; i = edge[i].next)
		{
			v = edge[i].v;
			w = edge[i].w;

			if (dist[v] > dist[u] + (long long)w)
			{
				dist[v] = dist[u] + (long long)w;
				if (!flag[v])
					heap.push(std::make_pair(dist[v], v));
			}
		}
	}

	return dist[dest];
}
