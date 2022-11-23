/********************************************************************
** E5 - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAX_NUM = 100004;

struct Point
{
	double x;
	double y;
};

Point point[MAX_NUM];
Point stack[MAX_NUM];
Point temp[MAX_NUM];
int top;
int n;
double cross(const Point& p1, const Point& p2, const Point& p0);
double distance(const Point& p1, const Point& p2);

struct ComparePoint
{
	bool operator()(const Point& p1, const Point& p2)
	{
		double c = cross(p1, p2, point[1]);
		if (c < 0.0)
			return false;
		if (c == 0.0 && distance(p1, point[1]) > distance(p2, point[1]))
			return false;
		return true;
	};
};

void graham()
{
	std::sort(point + 2, point + 1 + n, ComparePoint());
	stack[1] = point[1];
	stack[2] = point[2];
	top = 2;
	n++;
	point[n] = point[1];

	for (int i = 3; i <= n; i++)
	{
		while ((top > 1) && cross(stack[top], point[i], stack[top - 1]) <= 0.0)
			top--;
		stack[++top] = point[i];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lf %lf", &point[i].x, &point[i].y);
		temp[i] = point[i];
		if ((point[i].y < point[1].y) || (point[i].y == point[1].y && point[i].x < point[1].x))
			std::swap(point[1], point[i]);
	}

	top = 0;
	graham();
	if (top == 2)
	{
		double m = 0.0;

		std::sort(temp + 1, temp + n, ComparePoint());
		m = distance(temp[1], temp[n - 1]);
		printf("%.6f\n", sqrt(m));

		return 0;
	}

	stack[top + 1] = stack[1];
	int j = 2;
	double ans = 0.0;
	for (int i = 1; i <= top; i++)
	{
		while (std::abs(cross(stack[i], stack[i + 1], stack[j])) \
			< std::abs(cross(stack[i], stack[i + 1], stack[j + 1])))
		{
			j++;
			if (j > top)
				j = 1;
		}
		ans = std::max(ans, distance(stack[i], stack[j]));
	}

	printf("%.6f\n", sqrt(ans));

	return 0;
}

double cross(const Point& p1, const Point& p2, const Point& p0)
{
	double x1 = p1.x - p0.x;
	double y1 = p1.y - p0.y;
	double x2 = p2.x - p0.x;
	double y2 = p2.y - p0.y;

	return (x1 * y2 - x2 * y1);
}

double distance(const Point& p1, const Point& p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;

	return dx * dx + dy * dy;
}
