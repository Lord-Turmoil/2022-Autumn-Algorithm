/********************************************************************
** E2 - G
*/

#include <cstdio>
#include <cmath>
#include <functional>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int FACTOR_NUM = 100000;

int factor[FACTOR_NUM];
int factorNum;
bool isSquare;

void getFactor(int n);
void showFactor();

// How many m from 1 to n.
int getCount(int& n, int m);
// C(m, n) in k
int calc(int m, int n);

int main()
{
	int t;
	int m, n;
	int k;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d %d", &m, &n, &k);
		getFactor(k);
		printf("%d\n", calc(m, n));
	}

	return 0;
}

// n >= 2
// factor[] is decreasing.
void getFactor(int n)
{
	int q = std::max((int)sqrt(n), 2);
	
	factorNum = 0;
	isSquare = false;
	for (int i = n; i >= q; i--)
	{
		if (n % i == 0)
		{
			factor[factorNum++] = i;
			if (n / i == i)
				isSquare = true;
		}
	}
}

void showFactor()
{
	printf("\t%c ", isSquare ? '#' : '$');
	for (int i = 0; i < factorNum; i++)
		printf("%d ", factor[i]);
	putchar('\n');
}

int getCount(int& n, int m)
{
	int ret = 0;

	while (n % m == 0)
	{
		n /= m;
		ret++;
	}

	return ret;
}

int calc(int m, int n)
{
	// m * (m - 1) * ... * (m - n + 1)
	// n * (n - 1) * ... * 1
	int ret = 0;
	int cnt;
	int s;
	int n1, n2, n3;
	int acc1, acc2, acc3;	// accumulation... bad name. :(
	int f = 0;

	if (isSquare)
	{
		f = factor[factorNum - 1];
		factorNum--;
	}

	n1 = m;
	n2 = m - n;
	n3 = n;
	acc1 = acc2 = acc3 = 0;
	for (int i = 0; i < factorNum; i++)
	{
		s = factor[i];
		acc1 += getCount(n1, s);
		acc2 += getCount(n2, s);
		acc3 += getCount(n3, s);
	}

	ret = acc1 - acc2 - acc3;
	if (isSquare)
		ret += (getCount(n1, f) - getCount(n2, f) - getCount(n3, f)) / 2;

	return ret;
}
