/********************************************************************
** C4 - H
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

struct Interval
{
	int left;
	int right;
};

struct CompareInterval
{
	bool operator()(Interval i1, Interval i2)
	{
		if (i1.left == i2.left)
			return i1.right > i2.right;
		else
			return i1.left < i2.left;
	};
};

const int MAX_SIZE = 1000004;

Interval interval[MAX_SIZE];

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &interval[i].left, &interval[i].right);
	std::sort(interval, interval + n, CompareInterval());

	// special cases
	if (m == 0)
	{
		printf("0\n");
		return 0;
	}
	if (interval[0].left > 1)
	{
		printf("(=> <=)\n");
		return 0;
	}

	int last;
	int candidate;
	int ans = 1;
	bool flag = false;
	for (int i = 0; i < n; )
	{
		candidate = 0;
		last = interval[i].right;
		if (last >= m)
		{
			flag = true;
			break;
		}

		for (int j = i + 1; j < n; j++)
		{
			if (interval[j].left <= interval[i].right + 1)
			{
				if (interval[j].right > last)
				{
					last = interval[j].right;
					candidate = j;
				}
			}
			else
				break;
		}
		if (candidate == 0)
			break;
		i = candidate;
		ans++;
	}

	if (flag)
		printf("%d\n", ans);
	else
		printf("(=> <=)\n");

	return 0;
}
