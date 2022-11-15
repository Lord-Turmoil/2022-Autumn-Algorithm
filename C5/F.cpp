/********************************************************************
** C5 - F
*/


#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <queue>

const int MAX_VERTEX_NUM	= 1000004;
const int MAX_EDGE_NUM		= 5000004;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int v;
	int w;
	int next;
};

int		head[MAX_VERTEX_NUM];
Edge	edge[MAX_EDGE_NUM * 2];
bool	flag[MAX_VERTEX_NUM];
int		distSrc[MAX_VERTEX_NUM];
int		distDst[MAX_VERTEX_NUM];
int		edgestamp;

void addEdge(int u, int v, int w);
void _addSingleEdge(int u, int v, int w);
void dijkstra(int src, int dist[]);

int main()
{
	int n, m, k;
	int u, v, w;
	int ans;

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}

	dijkstra(1, distSrc);
	dijkstra(n, distDst);
	
	ans = INF;
	for (int i = 0; i < k; i++)
	{
		scanf("%d", &u);
		if (distSrc[u] + distDst[u] < ans)
			ans = distSrc[u] + distDst[u];
	}
	printf("%d\n", ans);

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

void dijkstra(int src, int dist[])
{
	std::priority_queue<
		std::pair<int, int>,
		std::vector<std::pair<int, int>>,
		std::greater<std::pair<int, int>>> heap;
	int u, v, w;

	memset(flag, 0, sizeof(flag));
	memset(dist, 0x3f, sizeof(int) * MAX_VERTEX_NUM);
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

			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				if (!flag[v])
					heap.push(std::make_pair(dist[v], v));
			}
		}
	}
}
