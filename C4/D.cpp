/********************************************************************
** C4 - D
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <algorithm>

const int MAX_ITEM_NUM = 1004;
const int MAX_VOLUME = 1000004;

struct Item
{
	int value;
	int cost;
	double ratio;

	void get()
	{
		scanf("%d %d", &value, &cost);
		ratio = (double)value / (double)cost;
	}
};

struct CompareItem
{
	bool operator()(Item i1, Item i2)
	{
		return i1.ratio > i2.ratio;
	};
};

Item item[MAX_ITEM_NUM];
long long dp[MAX_VOLUME];

int main()
{
	int n, v;

	scanf("%d %d", &n, &v);
	for (int i = 0; i < n; i++)
		item[i].get();
	std::sort(item, item + n, CompareItem());

	double ans = 0;
	for (int i = 0; (i < n) && (v > 0); i++)
	{
		if (item[i].cost <= v)
		{
			ans += (double)item[i].value;
			v -= item[i].cost;
		}
		else
		{
			ans += item[i].ratio * v;
			v = 0;
		}
	}

	printf("%.3f\n", ans);

	return 0;
}
