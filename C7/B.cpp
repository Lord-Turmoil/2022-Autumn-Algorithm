/********************************************************************
** C7 - B - Greedy
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>
#include <climits>

const int MAX_SIZE = 100004;

struct Brick
{
	long long number;
	long long value;
};

struct CompareBrick
{
	bool operator()(const Brick& b1, const Brick& b2)
	{
		return b1.value < b2.value;
	};
};

Brick brick[MAX_SIZE];
Brick* curBrick;
int brickNum;

long long timestamp[MAX_SIZE];
int stampNum;

long long curRatio;
long long ans;

// Work with n bricks.
bool work(long long n);
int main()
{
	int t;
	
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &brickNum);
		for (int i = 0; i < brickNum; i++)
			scanf("%lld %lld", &brick[i].number, &brick[i].value);
		scanf("%d", &stampNum);
		for (int i = 1; i <= stampNum; i++)
			scanf("%lld", &timestamp[i]);

		std::sort(brick, brick + brickNum, CompareBrick());
		std::sort(timestamp + 1, timestamp + 1 + stampNum);

		timestamp[stampNum + 1] = LLONG_MAX;
		stampNum++;

		ans = 0LL;
		curRatio = 1LL;
		curBrick = brick;
		for (int i = 1; i <= stampNum; i++)
		{
			if (!work(timestamp[i] - timestamp[i - 1]))
				break;
			curRatio++;
		}

		printf("%lld\n", ans);
	}

	return 0;
}

bool work(long long n)
{
	while (n > 0)
	{
		if (curBrick->number >= n)
		{
			curBrick->number -= n;
			ans += curBrick->value * n * curRatio;
			n = 0;
		}
		else
		{
			n -= curBrick->number;
			ans += curBrick->value * curBrick->number * curRatio;
			curBrick++;
			if (curBrick == brick + brickNum)
				return false;
		}
	}

	return true;
}
