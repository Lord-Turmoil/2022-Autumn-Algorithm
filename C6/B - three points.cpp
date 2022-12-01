/********************************************************************
** C6 - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

const int MAX_NUM = 100004;
const char YES_TEXT[] = "how?\n";
const char NO_TEXT[] = "boo how! boo how!\n";

struct Point
{
	long long x;
	long long y;
};

struct ComparePoint
{
	bool operator()(const Point& p1, const Point& p2)
	{
		if (p1.x == p2.x)
			return p1.y < p2.y;
		return p1.x < p2.x;
	};
};

long long cross(const Point& p1, const Point& p2, const Point& p0);

Point point[MAX_NUM];
int main()
{
	int t;
	int n;
	bool flag;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lld %lld", &point[i].x, &point[i].y);
		std::sort(point, point + n, ComparePoint());

		if (n < 3)
		{
			printf(NO_TEXT);
			continue;
		}

		flag = false;
		for (int i = 2; i < n; i++)
		{
			if (cross(point[i], point[i - 1], point[i - 2]) != 0)
			{
				flag = true;
				break;
			}
		}
		printf(flag ? YES_TEXT : NO_TEXT);
	}

	return 0;
}

long long cross(const Point& p1, const Point& p2, const Point& p0)
{
	long long x1 = p1.x - p0.x;
	long long y1 = p1.y - p0.y;
	long long x2 = p2.x - p0.x;
	long long y2 = p2.y - p0.y;

	return x1 * y2 - x2 * y1;
}
