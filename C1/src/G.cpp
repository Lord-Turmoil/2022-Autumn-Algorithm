/*
** G
*/
#include <cstdio>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 1024;

enum State
{
	NONE = 0,
	OFFENSIVE,
	DEFENSIVE
};

State state[SIZE];

State Observe(int n, int k);
int main()
{
	int t;
	int n, k;
	State result;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &k);
		result = Observe(n, k);

		if (result == OFFENSIVE)
			printf("~A~\n");
		else if (result == DEFENSIVE)
			printf("~B~\n");
		else
			printf("~C~\n");
	}

	return 0;
}

State Observe(int n, int k)
{
	// Special check.
	if (k == 1)
	{
		if (n & 1)
			return OFFENSIVE;
		else
			return DEFENSIVE;
	}

	// General check.
	for (int i = 0; i <= n; i++)
		state[i] = NONE;
	for (int i = 1; i <= n; i *= k)
		state[i] = OFFENSIVE;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j *= k)
		{
			// Here, state[i] can't be NONE.
			int t = i + j;
			if (t > n && state[t] == OFFENSIVE)
				continue;

			if (state[t] == NONE)
			{
				if (state[i] == OFFENSIVE)
					state[t] = DEFENSIVE;
				else
					state[t] = OFFENSIVE;
			}
			else	// state[t] == DEFENSIVE
			{
				if (state[i] == DEFENSIVE)
					state[t] = OFFENSIVE;
			}
		}
	}

	return state[n];
}
