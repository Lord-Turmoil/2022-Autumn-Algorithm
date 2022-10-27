/********************************************************************
** C3 - D
*/

#include <cstdio>
#include <climits>
#include <functional>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

const int MAX_SIZE = 1000004;

long long dp[MAX_SIZE];
int a[MAX_SIZE];
int n;

long long solve();
int main()
{
    int t;
    long long ans;

    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
            dp[i] = LLONG_MIN;
        }

        if (n == 1)
            ans = (long long)a[0];
        else
            ans = solve();

        printf("%lld\n", ans);
    }

    return 0;
}

long long solve()
{
    dp[0] = a[0];
    if (a[0] > a[1])
        dp[1] = a[0];
    else
        dp[1] = a[1];

    for (int i = 2; i < n; i++)
        dp[i] = std::max(dp[i - 2] + (long long)a[i], (long long)dp[i - 1]);

#ifdef INTERNAL
    for (int i = 0; i < n; i++)
        printf("%5lld ", dp[i]);
    putchar('\n');
#endif

    return dp[n - 1];
}
