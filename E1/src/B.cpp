/********************************************************************
** E1 - B
*/

#include <stdio.h>
#include <math.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

int find(int z);
int main(void)
{
	int z, k;
	int t;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &z, &k);
		if (k > 2)
			printf("0\n");
		else if (k == 1)
			printf("%d\n", z - 1);
		else
			printf("%d\n", find(z));
	}

	return 0;
}

int find(int z)
{
	int ret = 0;

	int i, j;
	long long i2, j2;
	long long z2 = 1LL * z * z;
	for (i = 1; i < z; i++)
	{
		i2 = 1LL * i * i;
		j2 = z2 - i2;
		j = (int)sqrt((double)j2);

		for (int t = -4; t <= 4; t++)
		{
			int j1 = j + t;
			if (j1 < 1)
				continue;
			j2 = 1LL * j1 * j1;
			if (i2 + j2 == z2)
			{
				ret++;
#ifdef INTERNAL
				printf("\t%d %d %d\n", i, j1, z);
#endif
				break;
			}
		}
	}

	return ret;
}
