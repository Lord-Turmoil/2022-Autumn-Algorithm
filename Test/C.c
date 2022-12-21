/********************************************************************
** Test - C
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <stdio.h>
#include <math.h>

const double EPSILON = 1e-5;

int is_zero(double x);
int is_equal(double x, double y);

int main(void)
{
	double a, b;
	double x, y;
	double n_rank, log_rank;

	scanf("%lf %lf %lf %lf", &a, &b, &x, &y);

	double b_x = pow(b, x);
	if (is_equal(b_x, a))
	{
		n_rank = log(a) / log(b);
		log_rank = y + 1;
	}
	else if (b_x < a)
	{
		n_rank = log(a) / log(b);
		log_rank = 0.0;
	}
	else
	{
		n_rank = x;
		log_rank = y;
	}

	if (is_zero(n_rank) && (is_zero(log_rank)))
	{
		printf("1\n");
	}
	else
	{
		// print n
		if (!is_zero(n_rank))
		{
			if (is_equal(n_rank, 1.0))
				printf("n");
			else
				printf("n^%.3f", n_rank);
		}
		if (!is_zero(log_rank))
		{
			if (is_equal(log_rank, 1.0))
				printf("log(n)");
			else
				printf("log^%.3f(n)", log_rank);
		}
		putchar('\n');
	}

	return 0;
}

int is_zero(double x)
{
	return is_equal(x, 0.0);
}

int is_equal(double x, double y)
{
	return fabs(x - y) < EPSILON;
}
