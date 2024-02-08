#include <bits/stdc++.h>
using namespace std;
#define maxN 100
#define maxA 1000
#define maxS (2 * maxA * maxN)
int n;
int a[maxN];
int dp[maxN + 1][maxS];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < maxS; s++) {
            dp[i][s] = dp[i-1][s];
            if (s >= a[i-1])
                dp[i][s] += dp[i-1][s - a[i-1]];
            if (s + a[i-1] < maxS)
                dp[i][s] += dp[i-1][s + a[i-1]];
            if (dp[i][s] > 3)
                dp[i][s] = 3;
        }
    }
    if (dp[n][0] > 1)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}
