/********************************************************************
** C4 - G
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

const int MAX_SIZE = 100004;

int cost[MAX_SIZE];
int main()
{
	int t;
	int n, m;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &cost[i]);
		std::sort(cost, cost + n);	// less to greater

		int left = 0;
		int right = n - 1;
		int ans = 0;
		while (right > left)
		{
			if (cost[left] + cost[right] <= m)
			{
				left++;
				right--;
			}
			else
				right--;

			ans++;
		}

		if (right == left)
			ans++;

		printf("%d\n", ans);
	}

	return 0;
}
