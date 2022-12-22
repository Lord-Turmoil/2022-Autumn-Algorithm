/********************************************************************
** Exam - G
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 100004;

// loop
char source[MAX_LENGTH << 1];
char pattern[MAX_LENGTH];
int next[MAX_LENGTH];

void initialize(char* s, int* f);
bool kmp(char* s1, char* s2, int* f);

int main()
{
	int t;
	int length;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", source);
		scanf("%s", &pattern);

		length = (int)strlen(source);
		for (int i = 0; i <= length; i++)
			source[i + length] = source[i];

		initialize(pattern, next);
		if (kmp(source, pattern, next))
			printf("Yes\n");
		else
			printf("No\n");
	}

	return 0;
}

void initialize(char* s, int* f)
{
	int lng = strlen(s);

	memset(f, 0xFF, sizeof(int) * lng);

	for (register int i = 1; i < lng; i++)
	{
		register int j = f[i - 1];

		while ((s[j + 1] != s[i]) && (j >= 0))
			j = f[j];
		if (s[j + 1] == s[i])
			f[i] = j + 1;
		else
			f[i] = -1;
	}
}

bool kmp(char* s1, char* s2, int* f)
{
	int lng1 = strlen(s1);
	int lng2 = strlen(s2);
	int i, j;

	initialize(s2, f);

	i = j = 0;
	while (i < lng1)
	{
		if (s1[i] == s2[j])
		{

			i++;
			j++;
			if (j == lng2)
			{
				// printf("%d ", i - lng2);
				j = f[j - 1] + 1;
				return true;
			}
		}
		else
		{
			if (j == 0)
				i++;
			else
				j = f[j - 1] + 1;
		}
	}

	return false;
}
