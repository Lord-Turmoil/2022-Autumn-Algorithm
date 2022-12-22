/********************************************************************
** E1 - G
*/

#include <cstdio>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int SIZE = 24;
const int MAX_SHIFT = 62;

int Min(int a, int b);
void Convert(int* arr, long long value);
int Length(int* arr);
int Distance(int* src, int* dest);
int main()
{
	int t;
	int n;
	int ans;
	int src[SIZE];
	int dest[SIZE];

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		Convert(src, n);
		ans = 0x7f7f7f7f;
		for (int i = 0; i < MAX_SHIFT; i++)
		{
			Convert(dest, 1LL << i);
			ans = Min(ans, Distance(src, dest));
		}
#ifdef INTERNAL
		printf("\t");
#endif
		printf("%d\n", ans);
	}

	return 0;
}

int Min(int a, int b)
{
	return (a < b) ? a : b;
}

void Convert(int* arr, long long value)
{
	int i = 0;
	while (value > 0)
	{
		arr[i++] = value % 10;
		value /= 10;
	}
	arr[i] = -1;
}

int Length(int* arr)
{
	int length = 0;
	
	while (arr[length] != -1)
		length++;

	return length;
}

int Distance(int* src, int* dest)
{
	int dist = 0;
	int srcLength = Length(src);
	int destLength = Length(dest);
	int i, j;

	i = srcLength - 1;
	j = destLength - 1;
	while ((i >= 0) && (j >= 0))
	{
		if (src[i] == dest[j])
		{
			i--;
			j--;
		}
		else
		{
			dist++;
			i--;
		}
	}

	dist += i + j + 2;

	return dist;
}
