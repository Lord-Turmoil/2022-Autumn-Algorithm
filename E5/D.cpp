/********************************************************************
** E5 - D
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cmath>

const int MAX_NUM = 400004;

struct Point
{
	long long x;
	long long y;
};

Point point[MAX_NUM];

long long cross(const Point& p1, const Point& p2);
int main()
{
	int t;
	int n;
	long long ans;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lld %lld", &point[i].x, &point[i].y);
		point[n] = point[0];

		ans = 0;
		for (int i = 0; i < n; i++)
			ans += cross(point[i], point[i + 1]);

		printf("%lld\n", std::abs(ans) / 2);
	}

	return 0;
}

long long cross(const Point& p1, const Point& p2)
{
	return (p1.x * p2.y - p2.x * p1.y);
}
