/********************************************************************
** C5 - C - Hull
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAX_SIZE = 3004;

struct Point
{
	double x;
	double y;

	Point() {}
	Point(double _x, double _y) : x(_x), y(_y) {}

	Point operator-(const Point& p) const
	{
		return Point(x - p.x, y - p.y);
	}

	double cross(const Point& p) const
	{
		return x * p.y - p.x * y;
	}

	double module() const
	{
		return std::sqrt(x * x + y * y);
	}
};

using Vector = Point;
Point pivot;
struct ComparePoint
{
	bool operator()(const Point& p1, const Point& p2)
	{
		if ((p1 - pivot).cross(p2 - pivot) > 0.0)
			return true;
		else
			return false;
	};
};

Point point[MAX_SIZE];
Point hull[MAX_SIZE];

int buildHull(int vertexNum);
int main()
{
	int t;
	int n;
	int hullSize;
	double ans;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%lf %lf", &point[i].x, &point[i].y);
			if ((point[i].y < point[0].y) && (i != 0))
				std::swap(point[i], point[0]);
		}

		hullSize = buildHull(n);
		ans = 0.0;
		for (int i = 1; i <= hullSize; i++)
			ans += (hull[i] - hull[i - 1]).module();

		printf("%.10f", ans);
	}

	return 0;
}

int buildHull(int vertexNum)
{
	pivot = point[0];
	std::sort(point + 1, point + vertexNum, ComparePoint());

	int top = 0;
	hull[0] = point[0];
	for (int i = 1; i < vertexNum; i++)
	{
		while ((top > 0) && ((hull[top] - hull[top - 1]).cross(point[i] - hull[top]) < 0.0))
			top--;
		hull[++top] = point[i];
	}
	hull[++top] = point[0];

	return top;
}
