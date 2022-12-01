/********************************************************************
** C6 - D
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>

const int MAX_LENGTH = 2024;

char buffer[MAX_LENGTH];
bool flag[MAX_LENGTH][MAX_LENGTH];

char* longest_palindrome(char* str, int* length);
int main()
{
	int t;
	int length;
	char* pos;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", buffer);
		pos = longest_palindrome(buffer, &length);
		printf("%d\n", length);
	}

	return 0;
}

char* longest_palindrome(char* str, int* length)
{
	int len = (int)strlen(str);
	int max_len = 1;
	int pos = 0;

	memset(flag, 0, sizeof(flag));

	for (int i = 0; i < len; i++)
	{
		flag[i][i] = true;
		if ((i < len - 1) && (str[i] == str[i + 1]))
		{
			flag[i][i + 1] = true;
			pos = i;
			max_len = 2;
		}
	}
	for (int k = 3; k <= len; k++)
	{
		for (int i = 0; i <= len - k; i++)
		{
			int j = i + k - 1;
			if (flag[i + 1][j - 1] && (str[i] == str[j]))
			{
				flag[i][j] = true;
				max_len = k;
				pos = i;
			}
		}
	}

	*length = max_len;

	return str + pos;
}
