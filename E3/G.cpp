/********************************************************************
** E3 - G
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <unordered_set>

const long long MOD = 998244353;
const int MAX_N = 1000000;
const int MAX_K = 1000000000;

const unsigned HAS_TRAP		= 0x1;
const unsigned HAS_NO_TRAP	= 0x0;
unsigned pre, cur;				// Whether level has trap.

int n, m, k;
long long master, slave;	// Three values.
long long ans;

void calc(unsigned pattern);
int main()
{
	std::unordered_set<int> traps;

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < m; i++)
	{
		int a;
		scanf("%d", &a);
		traps.insert(a);
	}

	// Handle level 1.
	master = 1LL;
	if (traps.find(1) != traps.end())
	{
		// Has trap in level 1.
		slave = 0;
		ans = (long long)(k - 1);
		pre = HAS_NO_TRAP;
	}
	else
	{
		slave = 1;
		ans = (long long)k;
		pre = HAS_TRAP;
	}

	for (int i = 2; i <= n; i++)
	{
		if (traps.find(i) != traps.end())
			cur = HAS_TRAP;
		else
			cur = HAS_NO_TRAP;

		calc((pre << 1) | cur);
	}
	ans = ((master * (k - 1)) % MOD + slave) % MOD;

	printf("%lld\n", ans);

	return 0;
}

void calc(unsigned pattern)
{
	long long temp;	// new master
	if (pattern & 0x2)	// pre has trap
	{
		temp = ((master * (k - 2)) % MOD + slave) % MOD;
		if (pattern & 0x1)	// cur has trap
			slave = 0;
		else				// cur has no trap
			slave = (master * (k - 1)) % MOD;
	}
	else				// pre has no trap
	{
		temp = ((master * (k - 2)) % MOD + slave) % MOD;
		if (pattern & 0x1)	// cur has trap
			slave = 0;
		else				// cur has no trap
			slave = (master * (k - 1)) % MOD;
	}
	master = temp;
	pre = cur;
}
