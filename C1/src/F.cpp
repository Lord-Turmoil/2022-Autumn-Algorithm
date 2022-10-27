#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 100005;

long long arr[SIZE];
long long temp[SIZE];

long long inverse_pair(long long a[], long long c, int left, int right);
int main()
{
	int n;
	long long k;
	long long ans;

	scanf("%d", &n);
	scanf("%lld", &k);
	for (int i = 0; i < n; i++)
		scanf("%lld", &arr[i]);
	ans = inverse_pair(arr, k, 0, n - 1);
	printf("%lld\n", ans);

	return 0;
}

long long inverse_pair(long long a[], long long c, int left, int right)
{
	if (left >= right)
		return 0;

	long long rv = 0;
	int mid = left + ((right - left) >> 1);
	int i, j, k;

	rv += inverse_pair(a, c, left, mid);
	rv += inverse_pair(a, c, mid + 1, right);

	//merge
	i = left;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= right)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
		{
			long long* it = std::upper_bound(&a[i], a + mid + 1, c * a[j]);
			if (it != a + mid + 1)
				rv += mid - (it - a) + 1;
			temp[k++] = a[j++];
		}
	}
	while (i <= mid)
		temp[k++] = a[i++];
	while (j <= right)
		temp[k++] = a[j++];
	for (i = 0; i < k; i++)
		a[left + i] = temp[i];

	return rv;
}
