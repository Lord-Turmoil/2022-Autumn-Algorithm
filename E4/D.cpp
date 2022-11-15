/********************************************************************
** E4 - D
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_VERTEX_NUM = 2010;
const int MAX_EDGE_NUM = 6010;
const int INF = 1000000000;

struct Edge
{
	int v;
	int w;
	int next;
};

Edge	edge[MAX_EDGE_NUM];
int		head[MAX_VERTEX_NUM];
int		dist[MAX_VERTEX_NUM];
int		length[MAX_VERTEX_NUM];
int		tag[MAX_VERTEX_NUM];
bool	flag[MAX_VERTEX_NUM];

int		edgestamp;

void addEdge(int u, int v, int w);
bool spfa(int src, int vertexNum);
int main()
{
	int n, m;
	int u, v, w;
	int t;

	scanf("%d", &t);
	while (t--)
	{
		edgestamp = 0;
		// memset(edge, 0, sizeof(edge));
		memset(head, 0, sizeof(head));
		memset(tag,  0, sizeof(tag));
		std::fill(dist, dist + MAX_VERTEX_NUM, INF);

		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &u, &v, &w);
			addEdge(u, v, w);
		}

		bool hasnegativeLoop = false;
		for (int i = 1; i <= n; i++)
		{
			if (tag[i] == 0)	// not found yet
			{
				if (spfa(i, n))
				{
					hasnegativeLoop = true;
					break;
				}
			}
		}

		if (hasnegativeLoop)
			printf("boo how\n");
		else
		{
			for (int i = 1; i <= n; i++)
				printf("%d ", (tag[i] == 1) ? dist[i] : INF);
			putchar('\n');
		}
	}

	return 0;
}

void addEdge(int u, int v, int w)
{
	edgestamp++;
	edge[edgestamp].v = v;
	edge[edgestamp].w = w;
	edge[edgestamp].next = head[u];
	head[u] = edgestamp;
}

bool spfa(int src, int vertexNum)
{
    std::queue<int> candidates;
    int u, v, w;

	memset(length, 0, sizeof(length));
	memset(flag, false, sizeof(flag));

	dist[src] = 0;
	length[src] = 1;

    candidates.push(src);
    flag[src] = true;
    while (!candidates.empty())
    {
        u = candidates.front();
        candidates.pop();
        flag[u] = false;
		tag[u] = src;
        for (int i = head[u]; i != 0; i = edge[i].next)
        {
            v = edge[i].v;
            w = edge[i].w;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
				length[v] = length[u] + 1;
				if (length[v] > vertexNum)
					return true;
                if (!flag[v])
                {
                    candidates.push(v);
                    flag[v] = true;
                }
            }
        }
    }

	return false;
}
