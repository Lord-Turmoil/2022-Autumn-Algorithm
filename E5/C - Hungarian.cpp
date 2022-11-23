/********************************************************************
** E5 - C -- Hungarian Algorithm
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int MAX_SIZE = 404;   // Not Found :P

std::vector<int> matrix[MAX_SIZE];
int match[MAX_SIZE];
int stamp[MAX_SIZE];
bool flag[MAX_SIZE];

struct Student
{
	int charm;
	int criteria;
};

Student boy[MAX_SIZE];
Student girl[MAX_SIZE];
int n;

bool canAttract(const Student& a, const Student& b);
void buildGraph();
bool dfs(const int u, const int tag);
int main()
{
	int ans;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &boy[i].charm);
	for (int i = 1; i <= n; i++)
		scanf("%d", &boy[i].criteria);
	for (int i = 1; i <= n; i++)
		scanf("%d", &girl[i].charm);
	for (int i = 1; i <= n; i++)
		scanf("%d", &girl[i].criteria);

	buildGraph();

	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (dfs(i, i))
			ans++;
	}
	printf("%d\n", ans);

	return 0;
}

bool canAttract(const Student& a, const Student& b)
{
	return (b.charm >= a.criteria) && (a.charm >= b.criteria);
}

void buildGraph()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (canAttract(boy[i], girl[j]))
				matrix[i].push_back(j);
		}
	}
}

bool dfs(const int u, const int tag)
{
	if (stamp[u] == tag)
		return false;
	stamp[u] = tag;
	for (auto v : matrix[u])
	{
		if ((match[v] == 0) || dfs(match[v], tag))
		{
			match[v] = u;
			return true;
		}
	}

	return false;
}
