/********************************************************************
** C6 - A
*/
#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <algorithm>

const int LENGTH = 1000005;

char str1[LENGTH];
char str2[LENGTH];
int next[LENGTH];

void initialize(char* s, int* f);
void kmp(char* s1, char* s2, int* f);
int main()
{
	scanf("%s %s", str1, str2);
	kmp(str1, str2, next);

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

void kmp(char* s1, char* s2, int* f)
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
				printf("%d ", i - lng2);
				j = f[j - 1] + 1;
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
}
