/********************************************************************
** C2 - A
*/

#include <cstdio>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_SIZE = 1024;
const int INF = 0x7f7f7f7f;

struct Point
{
	int x;
	int y;
};

Point points[MAX_SIZE];

constexpr int Min(int a, int b) { return (a < b) ? a : b; }
constexpr int Max(int a, int b) { return (a > b) ? a : b; }
constexpr int Abs(int a) { return (a < 0) ? (-a) : a; }

int Distance(Point p1, Point p2);
int main()
{
	int t;
	int n;
	int dist, ans;

	scanf("%d", &t);
	while (t--)
	{
		ans = INF;

		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d %d", &points[i].x, &points[i].y);
			for (int j = 0; j < i; j++)
			{
				dist = Distance(points[i], points[j]);
				ans = Min(ans, dist);
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}

int Distance(Point p1, Point p2)
{
	return Max(Abs(p1.x - p2.x), Abs(p1.y - p2.y));
}
