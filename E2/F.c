/********************************************************************
** E2 - F
** REFERENCE: https://www.cnblogs.com/Howe-Young/p/9499373.html
*/

#include <stdio.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#ifdef INTERNAL
typedef long long LargeInteger;
#else
typedef __int128 LargeInteger;
#endif

#define MAX_SIZE 1000006

int lower_bound[MAX_SIZE];
int upper_bound[MAX_SIZE];
int a[MAX_SIZE];
LargeInteger max_sum;
LargeInteger min_sum;

void get_min_lower_bound(void);
void get_min_upper_bound(void);
void get_max_lower_bound(void);
void get_max_upper_bound(void);

void get_min_sum(void);
void get_max_sum(void);

void print_answer(void);
void print(LargeInteger x);

int n;
int main(void)
{
	int t;
	
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);

		get_min_lower_bound();
		get_min_upper_bound();
		get_min_sum();

		get_max_lower_bound();
		get_max_upper_bound();
		get_max_sum();

		print_answer();
	}

	return 0;
}

void get_min_lower_bound(void)
{
	int bound;

	lower_bound[0] = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i] >= a[i - 1])
			lower_bound[i] = i;
		else
		{
			bound = i - 1;
			while ((bound >= 0) && (a[i] < a[bound]))
			{
				if (bound == lower_bound[bound])
					bound--;
				else
					bound = lower_bound[bound];
			}
			lower_bound[i] = bound + 1;
		}
	}
}

void get_min_upper_bound(void)
{
	int bound;

	upper_bound[n - 1] = n - 1;
	for (int i = n - 2; i >= 0; i--)
	{
		if (a[i] > a[i + 1])
			upper_bound[i] = i;
		else
		{
			bound = i + 1;
			while ((bound < n) && (a[i] <= a[bound]))
			{
				if (bound == upper_bound[bound])
					bound++;
				else
					bound = upper_bound[bound];
			}
			upper_bound[i] = bound - 1;
		}
	}
}

void get_max_lower_bound(void)
{
	int bound;

	lower_bound[0] = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i] <= a[i - 1])
			lower_bound[i] = i;
		else
		{
			bound = i - 1;
			while ((bound >= 0) && (a[i] > a[bound]))
			{
				if (bound == lower_bound[bound])
					bound--;
				else
					bound = lower_bound[bound];
			}
			lower_bound[i] = bound + 1;
		}
	}
}

void get_max_upper_bound(void)
{
	int bound;

	upper_bound[n - 1] = n - 1;
	for (int i = n - 2; i >= 0; i--)
	{
		if (a[i] < a[i + 1])
			upper_bound[i] = i;
		else
		{
			bound = i + 1;
			while ((bound < n) && (a[i] >= a[bound]))
			{
				if (bound == upper_bound[bound])
					bound++;
				else
					bound = upper_bound[bound];
			}
			upper_bound[i] = bound - 1;
		}
	}
}

void get_min_sum(void)
{
	LargeInteger temp;

	min_sum = 0;
	for (int i = 0; i < n; i++)
	{
		temp = (LargeInteger)(i - lower_bound[i] + 1) * (LargeInteger)(upper_bound[i] - i + 1);
		min_sum += temp * (LargeInteger)a[i];
	}
}

void get_max_sum(void)
{
	LargeInteger temp;

	max_sum = 0;
	for (int i = 0; i < n; i++)
	{
		temp = (LargeInteger)(i - lower_bound[i] + 1) * (LargeInteger)(upper_bound[i] - i + 1);
		max_sum += temp * (LargeInteger)a[i];
	}
}

void print_answer(void)
{
	print(max_sum - min_sum);
	putchar('\n');
}

void print(LargeInteger x)
{
	if (x < 10)
	{
		printf("%d", (int)x);
		return;
	}

	print(x / 10);

	printf("%d", (int)(x % 10));
}
