/********************************************************************
** E4 - E
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_VERTEX_NUM = 1000004;
const int MAX_EDGE_NUM = 2000004;

struct Edge
{
    int v;
    int next;
};

Edge edge[MAX_EDGE_NUM];
int head[MAX_VERTEX_NUM];
bool visited[MAX_VERTEX_NUM];
int sequence[MAX_VERTEX_NUM];
int sequenceSize;
int edgestamp;

void addEdge(int u, int v);
void toposort(int vertexNum);
void dfs(int u);
bool check();

int main()
{
    int t;
    int n, m;
    int u, v;

    scanf("%d", &t);
    while (t--)
    {
        edgestamp = 0;
        sequenceSize = 0;
        memset(head, 0, sizeof(head));
        memset(visited, 0, sizeof(visited));

        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d", &u, &v);
            addEdge(u, v);
        }

        toposort(n);
        if (check())
            printf("yy\n");
        else
            printf("nn\n");
    }

    return 0;
}

void addEdge(int u, int v)
{
    edgestamp++;
    edge[edgestamp].v = v;
    edge[edgestamp].next = head[u];
    head[u] = edgestamp;
}

void toposort(int vertexNum)
{
    for (int i = 1; i <= vertexNum; i++)
    {
        if (!visited[i])
            dfs(i);
    }
}

void dfs(int u)
{
    for (int i = head[u]; i != 0; i = edge[i].next)
    {
        if (!visited[edge[i].v])
            dfs(edge[i].v);
    }
    visited[u] = true;

    sequence[sequenceSize++] = u;
}

bool check()
{
    int u, v;
    bool flag;
    for (int i = sequenceSize - 1; i > 0; i--)
    {
        u = sequence[i];
        v = sequence[i - 1];
        flag = false;
        for (int j = head[u]; j != 0; j = edge[j].next)
        {
            if (edge[j].v == v)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            return false;
    }

    return true;
}
