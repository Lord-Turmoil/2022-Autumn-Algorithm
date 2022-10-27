/********************************************************************
** C2 - C
*/
#include <stdio.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define MOD 998244353LL
#define UPPER_BOUND 1000000
#define MAX_SIZE (UPPER_BOUND + 4)

void find(void);

long long ans[MAX_SIZE];
int main(void)
{
	int t;
	int n;

	find();
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		printf("%lld\n", ans[n]);
	}

	return 0;
}

/********************************************************************
** f(n) =   f(n - 1)
**        + f(n - 2)
**        + f(n - 3) * 4
**        + f(n - 4) * 2
** let f(0) = 1
*/
void find(void)
{
	ans[0] = 1;
	ans[1] = 1;
	ans[2] = 2;
	ans[3] = 7;

	for (int i = 4; i <= UPPER_BOUND; i++)
	{
		ans[i] = ans[i - 1];
		ans[i] = (ans[i] + ans[i - 2]) % MOD;
		ans[i] = (ans[i] + (ans[i - 3] * 4) % MOD) % MOD;
		ans[i] = (ans[i] + (ans[i - 4] * 2) % MOD) % MOD;
	}
}
