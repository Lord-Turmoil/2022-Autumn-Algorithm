/********************************************************************
** C5 - H -- Closest point pair.
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAX_SIZE = 500004;
const double INF = 1e10;

struct Point
{
	double x;
	double y;
};

int ind[MAX_SIZE];
Point point[MAX_SIZE];

struct ComparePointY
{
	bool operator()(int a, int b)
	{
		return point[a].y < point[b].y;
	};
};

struct ComparePoint
{
	bool operator()(const Point& a, const Point& b)
	{
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	};
};

double distance(int i, int j)
{
	double dx = point[i].x - point[j].x;
	double dy = point[i].y - point[j].y;

	return std::sqrt(dx * dx + dy * dy);
}

double merge(int left, int right)
{
	double dist = INF;
	
	if (left >= right - 1)
		return dist;
	if (left == right - 2)
		return distance(left, left + 1);

	int mid = (left + right) >> 1;
	double distLeft = merge(left, mid);
	double distRight = merge(mid, right);
	dist = std::min(distLeft, distRight);

	int k = 0;
	for (int i = left; i < right; i++)
	{
		if (std::abs(point[mid].x - point[i].x) < dist)
			ind[k++] = i;
	}
	std::sort(ind, ind + k, ComparePointY());
	for (int i = 0; i < k; i++)
	{
		for (int j = i + 1; (j < k) && (point[ind[j]].y - point[ind[i]].y < dist); j++)
		{
			double temp = distance(ind[i], ind[j]);
			dist = std::min(dist, temp);
		}
	}
	
	return dist;
}

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf", &point[i].x, &point[i].y);
	std::sort(point, point + n, ComparePoint());
	printf("%.4f\n", merge(0, n));

	return 0;
}
