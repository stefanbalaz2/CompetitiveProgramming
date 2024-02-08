#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int ans = 0;
    int q; scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r; scanf("%d %d", &l, &r);
        int cur = 0;
        for (int m = l; m <= r; m++) {
            int cnt_larger = 0;
            for (int j = l; j <= r; j++) {
                if (a[j] > a[m]) cnt_larger += 1;
            }
            printf("%d %d %d %d\n", i, m, cnt_larger, cnt_larger * a[m]);
            cur = max(cur, cnt_larger * a[m]);
        }
        ans = max(ans, cur);
    }
    printf("%d\n", ans);
    return 0;
}
