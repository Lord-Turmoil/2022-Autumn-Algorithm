/*
** B
*/
#include <cstdio>
#include <cmath>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 30010;
const int MOD = 10007;

int a[SIZE];
int b[SIZE];

int calc(int x, int power, int* arr);
int main()
{
	int n, m;
	int x, y;
	int q;

	// Read in an and bn.
	scanf("%d", &n);
	for (int i = n; i >= 0; i--)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = m; i >= 0; i--)
		scanf("%d", &b[i]);

	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		scanf("%d %d", &x, &y);

#ifdef INTERNAL
		printf("%d\n", calc(x, n, a));
		printf("%d\n", calc(y, m, b));
#endif

		printf("%d\n", (calc(x, n, a) * calc(y, m, b)) % MOD);
	}

	return 0;
}

int calc(int x, int power, int* arr)
{
	int ret = arr[0];

	for (int i = 1; i <= power; i++)
		ret = ((ret * x) % MOD + arr[i]) % MOD;

	return ret;
}
