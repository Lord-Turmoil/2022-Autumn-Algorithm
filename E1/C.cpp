#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 100005;
int pool[SIZE];
int pos[SIZE];
int main()
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> candidates;

	int t;
	int n, k;
	int num;

	scanf("%d", &t);
	while (t--)
	{
		int m = 0;
		scanf("%d %d", &k, &n);
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < n; j++)
				scanf("%d", &pool[m++]);
			pos[i] = i * n;
		}
		for (int i = 0; i < k; i++)
			candidates.emplace(pool[pos[i]], i);

		while (!candidates.empty())
		{
			int m = candidates.top().first;
			int id = candidates.top().second;
			candidates.pop();

			printf("%d ", m);

			pos[id]++;
			if (pos[id] < (id + 1) * n)
			{
				candidates.push(std::make_pair(pool[pos[id]], id));
			}
		}
		putchar('\n');
	}

	return 0;
}
