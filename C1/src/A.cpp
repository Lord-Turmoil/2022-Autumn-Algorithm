/*
** A
*/
#include <cstdio>
#include <cmath>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const char RESULT_A[] = R"(n^{\log_ba})";
const char RESULT_B[] = R"(n^k\log n)";
const char RESULT_C[] = R"(n^k)";

const double EPSILON = 1.0;

long long qpow(long long x, long long p);
int main()
{
	int n;
	long long a, b, k;
	long long bk;
	double da, db, dk;
	double logba;
	const char* result;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld %lld %lld", &a, &b, &k);
		da = (double)a;
		db = (double)b;
		dk = (double)k;
		logba = log(da) / log(db);

		if (fabs(logba - dk) < EPSILON)
		{
			bk = qpow(b, k);
			if (a == bk)
				result = RESULT_B;
			else if (a > bk)
				result = RESULT_A;
			else
				result = RESULT_C;
		}
		else if (logba > dk)
			result = RESULT_A;
		else
			result = RESULT_C;
		
		printf("%s\n", result);
	}

	return 0;
}

long long qpow(long long x, long long p)
{
	long long result = 1;
	long long base = x;
	
	while (p)
	{
		if (p & 1)
			result *= base;
		base *= base;
		p >>= 1;
	}

	return result;
}
