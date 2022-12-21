/********************************************************************
** C6 - E - Suffix Array
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_LENGTH = 100004;
const int MAX_VALUE = 256;	// Well, max ASCII for string.

class SuffixArray
{
public:
	// Well, str[0] is invalid, we use str[1 to n].
	void Build(char* str);
	
	int SAOf(int i) const { return sa[i]; }
	int RankOf(int i) const { return rank[i]; }

private:
	// Temp array.
	int a[MAX_LENGTH];
	int b[MAX_LENGTH];
	int c[MAX_LENGTH];

	// the thing.
	int sa[MAX_LENGTH];
	int rank[MAX_LENGTH];	// Warning, there exists std::rank.
};

void SuffixArray::Build(char* str)
{
	int n = (int)strlen(str + 1);
	int m = MAX_VALUE;

	// Initialization.
	int upper = std::min(n * 2, MAX_LENGTH);
	for (int i = 0; i <= upper; i++)
		a[i] = b[i] = sa[i] = rank[i] = 0;
	for (int i = 0; i < m; i++)
		c[i] = 0;
	for (int i = 1; i <= n; i++)
		c[a[i] = str[i]]++;
	for (int i = 1; i <= m; i++)
		c[i] += c[i - 1];
	for (int i = n; i > 0; i--)
		sa[c[a[i]]--] = i;

	int* x = a;
	int* y = b;
	for (int j = 1, p = 0; j <= n && p != n + 1; j <<= 1)
	{
		p = 0;
		for (int i = n - j + 1; i <= n; i++)
			y[++p] = i;
		for (int i = 1; i <= n; i++)
		{
			if (sa[i] > j)
				y[++p] = sa[i] - j;
		}
		for (int i = 1; i <= m; i++)
			c[i] = 0;
		for (int i = 1; i <= n; i++)
			c[x[y[i]]]++;
		for (int i = 1; i <= m; i++)
			c[i] += c[i - 1];
		for (int i = n; i > 0; i--)
			sa[c[x[y[i]]]--] = y[i];

		std::swap(x, y);

		x[sa[1]] = 1;
		p = 2;
		for (int i = 2; i <= n; i++)
		{
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && \
				(y[sa[i] + j] == y[sa[i - 1] + j])) ? p - 1 : p++;
		}
		m = p;
	}
	for (int i = 1; i <= n; i++)
		rank[sa[i]] = i;
}

char buffer[MAX_LENGTH];
SuffixArray suffixArray;

int main()
{
	int t;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", buffer + 1);
		suffixArray.Build(buffer);
		printf("%s\n", buffer + suffixArray.SAOf(1));
	}

	return 0;
}

