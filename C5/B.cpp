/********************************************************************
** C5 - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cmath>

long long absolute(long long a)
{
	return (a < 0) ? -a : a;
}

int main()
{
	long long x1, y1;
	long long x2, y2;
	long long x3, y3;

	long long p1x, p1y;
	long long p2x, p2y;

	long long ans;

	int t;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld %lld", &x1, &y1);
		scanf("%lld %lld", &x2, &y2);
		scanf("%lld %lld", &x3, &y3);

		p1x = x2 - x1;
		p1y = y2 - y1;
		p2x = x3 - x1;
		p2y = y3 - y1;

		ans = absolute(p1x * p2y - p2x * p1y);

		printf("%lld.%1d\n", ans / 2LL, (ans & 1LL) ? 5 : 0);
	}

	return 0;
}
