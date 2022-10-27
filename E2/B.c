/********************************************************************
** E2 - B
*/

#include <stdio.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define UPPER_BOUND 1000001

#define MOD 998244353LL

long long dp[UPPER_BOUND];
long long aux[UPPER_BOUND];

void find(void);
int main(void)
{
	int t;
	int n;

	find();

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		printf("%lld\n", dp[n]);
	}

	return 0;
}

/********************************************************************
** dp[i] =   dp[i - 1] 
**         + dp[i - 2]
**         + dp[i - 3] * 6
**         + dp[i - 4] * 4
**         + dp[i - 5] * 2
*/
void find(void)
{
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 9;
	dp[4] = 21;
	aux[0] = 1;
	for (int i = 1; i < 5; i++)
		aux[i] = aux[i - 1] + dp[i];

	for (int i = 5; i < UPPER_BOUND; i++)
	{
		dp[i] = (dp[i] + dp[i - 1]) % MOD;
		dp[i] = (dp[i] + dp[i - 2]) % MOD;
		dp[i] = (dp[i] + (dp[i - 3] * 6) % MOD) % MOD;
		dp[i] = (dp[i] + (dp[i - 4] * 4) % MOD) % MOD;
		
		dp[i] = (dp[i] + (aux[i - 5] * 2) % MOD) % MOD;

		aux[i] = (aux[i - 1] + dp[i]) % MOD;
	}
}


