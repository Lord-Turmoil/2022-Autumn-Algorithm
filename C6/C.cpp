/********************************************************************
** C6 - C
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>

typedef unsigned long long hash_t;

const int MAX_LENGTH = 1000004;
const hash_t KEY = 29ull;

hash_t qpow(hash_t base, unsigned power)
{
    hash_t rv = 1;

    while (power > 0)
    {
        if (power & 1)
            rv = rv * base;
        base = base * base;
        power >>= 1;
    }

    return rv;
}

char buffer[MAX_LENGTH];
int main()
{
    int t;
    int length;
    hash_t prefix;
    hash_t suffix;

    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", buffer);

        prefix = suffix = 0;
        length = (int)strlen(buffer);
        for (int i = 0; i < length; i++)
        {
            int j = length - i - 1;

            prefix = prefix * KEY + (hash_t)(buffer[i]);
            suffix = ((hash_t)(buffer[j]) * qpow(KEY, (unsigned)i)) + suffix;

            if (prefix == suffix)
                printf("%d ", i + 1);
        }

        putchar('\n');
    }

    return 0;
}

