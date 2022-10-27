/********************************************************************
** E2 - D
*/

#include <stdio.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

int main(void)
{
	int n, m;
	int op;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &op);
		if (op == 1)
			scanf("%*d %*d");
		else if (op == 2)
			scanf("%*d %*d %*d");
		else
		{
			scanf("%*d %*d");
			printf("0\n");
		}
	}

	return 0;
}

