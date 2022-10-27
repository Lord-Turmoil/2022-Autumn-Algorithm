/********************************************************************
** C2 - D
*/

#include <cstdio>
#include <deque>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

using namespace std;

const int MAX_N = 10000086;

unsigned seed;
unsigned Rand()
{
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	return seed;
}

// int fa[MAX_N];
unsigned a[MAX_N];

int main()
{
	int t, n, k;
	deque<pair<unsigned, int>> candidates;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d %u", &n, &k, &seed);
		k--;
		for (int i = 1; i <= n; i++)
			a[i] = Rand();

		unsigned ans = 0;
		for (int i = 1; i <= n; i++)
		{
			while (!candidates.empty() && (i - candidates.front().second > k))
				candidates.pop_front();
			while (!candidates.empty() && (candidates.back().first < a[i]))
				candidates.pop_back();
			candidates.push_back(make_pair(a[i], i));
			ans += candidates.front().first ^ i;
		}

		printf("%u\n", ans);

		candidates.clear();
	}
}
