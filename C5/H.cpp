/********************************************************************
** C5 - H - WA
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAX_NUM = 200004;
const double INF = 1e7;

struct Point
{
    double x;
    double y;
};

Point point[MAX_NUM];
int id[MAX_NUM];

struct ComparePointInY
{
    bool operator()(int a, int b)
    {
        return point[a].y < point[b].y;
    };
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


double dist(const Point& p1, const Point& p2);
double solve(int left, int right);  // [left, right)
int main()
{
    int n;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf %lf", &point[i].x, &point[i].y);
    std::sort(point, point + n, ComparePoint());
    printf("%.4f\n", solve(0, n));

    return 0;
}

double dist(const Point& p1, const Point& p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y * p2.y));
}

double solve(int left, int right)
{
    double ret = INF;

    if (right <= left + 1)
        return ret;

    if (right == left + 2)
        return dist(point[left], point[left + 1]);

    int mid = left + ((right - left) >> 1);
    ret = std::min(solve(left, mid), solve(mid, right));

    int k = 0;
    for (int i = left; i < right; i++)
    {
        if (std::abs(point[mid].x - point[i].x) < ret)
            id[k++] = i;
    }

    std::sort(id, id + k, ComparePointInY());

    double d;
    for (int i = 0; i < k - 1; i++)
    {
        for (int j = i + 1; (j < k) && (point[id[j]].y - point[id[i]].y < ret); j++)
        {
            d = dist(point[id[i]], point[id[j]]);
            if (d < ret)
                ret = d;
        }
    }

    return ret;
}

