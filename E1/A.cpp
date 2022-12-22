/********************************************************************
** E1 - A
*/

#include <stdio.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define SIZE 100000

typedef struct tagTerm
{
	int c;
	int p;
} Term;

Term polyA[SIZE + 1];
Term polyB[SIZE + 1];
Term polyC[SIZE * 2 + 1];

int main(void)
{
	int n, m;
	int t;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &polyA[i].c);
		for (int i = 0; i < n; i++)
			scanf("%d", &polyA[i].p);

		scanf("%d", &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &polyB[i].c);
		for (int i = 0; i < n; i++)
			scanf("%d", &polyB[i].p);

		int a, b, k;
		a = b = k = 0;
		while (a < n && b < m)
		{
			if (polyA[a].p == polyB[b].p)
			{
				if (polyA[a].c + polyB[b].c != 0)
				{
					polyC[k].c = polyA[a].c + polyB[b].c;
					polyC[k].p = polyA[a].p;
					k++;
				}
				a++;
				b++;
			}
			else if (polyA[a].p < polyB[b].p)
				polyC[k++] = polyA[a++];
			else
				polyC[k++] = polyB[b++];
		}
		while (a < n)
			polyC[k++] = polyA[a++];
		while (b < m)
			polyC[k++] = polyB[b++];

		printf("%d\n", k);
		for (int i = 0; i < k; i++)
			printf("%d ", polyC[i].c);
		putchar('\n');
		for (int i = 0; i < k; i++)
			printf("%d ", polyC[i].p);
		putchar('\n');
	}

	return 0;
}
