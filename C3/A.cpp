/********************************************************************
** C3 - A
*/

#include <cstdio>
#include <functional>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_LENGTH = 10004;

long long price[MAX_LENGTH];
long long dp[MAX_LENGTH];
int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &price[i]);

	dp[1] = price[1];
	for (int i = 2; i <= n; i++)
	{
		dp[i] = price[i];
		for (int j = 1; j < i; j++)
			dp[i] = std::max(dp[i], dp[i - j] + price[j]);
	}

	printf("%lld\n", dp[n]);

	return 0;
}
