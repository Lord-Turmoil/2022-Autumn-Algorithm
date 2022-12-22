/********************************************************************
** Exam - H
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

const int MAX_SIZE = 1024;
const long long THRESHOLD = 1000000000;

inline long long gcd(long long a, long long b)
{
	long long c;
	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}

	return a;
}

inline long long lcm(long long a, long long b)
{
	return a * b / gcd(a, b);
}

long long a[MAX_SIZE];

void solve();
int main()
{
	int t;

	scanf("%d", &t);
	while (t--)
		solve();

	return 0;
}

void solve()
{
	int n;
	long long ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	std::sort(a, a + n);
	ans = a[0];
	for (int i = 1; i < n; i++)
	{
		ans = lcm(ans, a[i]);
		if (ans > THRESHOLD)
		{
			ans = -1;
			break;
		}
	}

	printf("%lld\n", ans);
}


