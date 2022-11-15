/********************************************************************
** E4 - F
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>

const int MAX = INT_MAX;

const int MAX_VERTEX_NUM = 204;
const int MAX_EDGE_NUM = 5004;
const long long INF = LLONG_MAX;

struct Edge
{
	int v;
	int next;
	long long capacity;
};

Edge edge[MAX_EDGE_NUM << 1];
int head[MAX_VERTEX_NUM];
int current[MAX_VERTEX_NUM];
int depth[MAX_VERTEX_NUM];
int edgestamp = 1;

int vertexNum, edgeNum;
int source, sink;

void addEdge(int u, int v, long long c);
bool bfs();
long long dfs(int u, long long flow);
long long dinic();
int main() {
	int t;
	int u, v, c;

	scanf("%d", &t);
	while (t--)
	{
		edgestamp = 1;
		memset(head, 0, sizeof(head));

		scanf("%d %d", &vertexNum, &edgeNum);
		scanf("%d %d", &source, &sink);

		for (int i = 0; i < edgeNum; i++)
		{
			scanf("%d %d %d", &u, &v, &c);
			addEdge(u, v, c);
			addEdge(v, u, 0);
		}

		printf("%lld\n", dinic());
	}

	return 0;
}

void addEdge(int u, int v, long long c)
{
	edgestamp++;
	edge[edgestamp].v = v;
	edge[edgestamp].capacity = c;
	edge[edgestamp].next = head[u];
	head[u] = edgestamp;
}

bool bfs()
{
	std::queue<int> candidates;
	int u, v;

	memset(depth, 0xff, sizeof(depth));

	candidates.push(source);
	depth[source] = 0;
	current[source] = head[source];
	while (!candidates.empty())
	{
		u = candidates.front();
		candidates.pop();
		for (int i = head[u]; i != 0; i = edge[i].next)
		{
			v = edge[i].v;
			if ((depth[v] == -1) && (edge[i].capacity > 0))
			{
				depth[v] = depth[u] + 1;
				current[v] = head[v];
				candidates.push(v);

				if (v == sink)
					return true;
			}
		}
	}

	return false;
}

long long dfs(int u, long long flow)
{
	if (u == sink)
		return flow;

	long long rv_flow = 0LL;
	long long cur_flow;
	int v;

	for (int i = current[u]; i != 0; i = edge[i].next)
	{
		current[u] = i;
		v = edge[i].v;
		if ((depth[v] == depth[u] + 1) && (edge[i].capacity > 0))
		{
			cur_flow = dfs(v, std::min(flow, edge[i].capacity));
			if (cur_flow == 0)
				depth[v] = -1;
			
			edge[i].capacity -= cur_flow;
			edge[i ^ 1].capacity += cur_flow;

			rv_flow += cur_flow;
			flow -= cur_flow;

			if (flow == 0)
				break;
		}
	}

	return rv_flow;
}

long long dinic()
{
	long long ret = 0LL;

	while (bfs())
		ret += dfs(source, INF);

	return ret;
}
