/********************************************************************
** E3 - A
*/

#include <cstdio>
#include <queue>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

int main()
{
	int n;
	long long length;

	std::priority_queue<long long, std::vector<long long>, std::greater<long long>> heap;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &length);
		heap.push(length);
	}

	long long ans = 0;
	long long left, right;

	while (heap.size() > 1)
	{
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();

		length = left + right;
		heap.push(length);

		ans += length * 2;
	}

	printf("%lld\n", ans);

	return 0;
}
