/********************************************************************
** C4 - B
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

const int MAX_SIZE = 1000004;

// [start, end)
struct Interval
{
	int start;
	int end;
};

struct CompareInterval
{
	bool operator()(Interval i1, Interval i2)
	{
		return i1.end < i2.end;
	};
};

Interval interval[MAX_SIZE];
int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &interval[i].start, &interval[i].end);

	std::sort(interval, interval + n, CompareInterval());

	int last = 0;
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (interval[i].start >= last)
		{
			ans++;
			last = interval[i].end;
		}
	}

	printf("%d\n", ans);

	return 0;
}

