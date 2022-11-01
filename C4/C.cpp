/********************************************************************
** C4 - C
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

const int MAX_ROD_NUM = 1004;
const int MAX_VOLUME = 100004;

int value[MAX_ROD_NUM];
int cost[MAX_ROD_NUM];
long long dp[MAX_VOLUME];
int main()
{
	int n, v;

	scanf("%d %d", &n, &v);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &value[i], &cost[i]);


	for (int i = 0; i < n; i++)
	{
		for (int j = v; j >= cost[i]; j--)
			dp[j] = std::max(dp[j], dp[j - cost[i]] + (long long)value[i]);
	}

	printf("%lld\n", dp[v]);

	return 0;
}
