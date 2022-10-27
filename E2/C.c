/********************************************************************
** E2 - C
*/

#include <stdio.h>
#include <string.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define MAX_SIZE 12

#ifdef INTERNAL
int combination(int n, int m)
{
	int ret = 1;
	int nume = n - m + 1;
	for (int i = 1; i <= m; i++)
	{
		ret = ret * nume / i;
		nume++;
	}

	return ret;
}
#endif

// C(0, 0) -> C(10, 5)
const int COMB[] = { 1, 1, 2, 3, 6, 10, 20, 35, 70, 126, 252 };

int group[MAX_SIZE];
int n, m, size;
int total;

/********************************************************************
** Select size elements out of n elements.
** Value starts from start, to fill in position i.
*/
void dfs(int start, int pos);
int main(void)
{
	int t;
	
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		size = (n > 1) ? (n / 2) : 1;
		if (m > COMB[n])
			printf("-1\n");
		else
		{
			total = 0;
			dfs(1, 0);
		}
	}

	return 0;
}

void dfs(int start, int pos)
{
	if (total == m)
		return;

	if (pos == size)
	{
#ifdef INTERNAL
		printf("\t> ");
#endif
		printf("%d ", size);
		for (int j = 0; j < size; j++)
			printf("%d ", group[j]);
		putchar('\n');
		total++;

		return;
	}

	int upper = n - size + pos + 1;
	for (int i = start; i <= upper; i++)
	{
		group[pos] = i;

		dfs(i + 1, pos + 1);

		if (total == m)
			break;
	}
}
