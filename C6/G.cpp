/********************************************************************
** C6 - G
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>

template<typename T>
T gcd(T a, T b)
{
	T c;

	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}

	return a;
}

int main()
{
	int t;
	long long a, b;
	long long numerator;
	long long denominator;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%lld %lld", &a, &b);
		numerator = 360LL * b;
		denominator = 180LL * b - 2LL * a;
		printf("%lld\n", numerator / gcd(numerator, denominator) - 1);
	}

	return 0;
}
