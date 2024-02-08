#include <bits/stdc++.h>
using namespace std;

int n, x;

void print(vector<int> &p) {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (p[i] != i)
            cnt++;
    printf("%d\n", n - cnt/2);
    for (int i = 1; i <= n; i++)
        printf("%d ", p[i]);
    printf("\n");
}

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d %d", &n, &x);


        set<int> s;
        vector<int> p(n + 1, 0);
        for (int i = 1; i <= n; i++)
            s.insert(i);

        if (x == n + 1) {
            int mode = 0;
            int l = 1, r = n;
            for (int i = 0; i < n; i++) {
                if (mode == 0) {
                    auto it = s.end();
                    it--;
                    s.erase(it);
                    p[r] = *it;
                    r--;
                } else if (mode == 1) {
                    auto it = s.end();
                    it--;
                    s.erase(it);
                    p[l] = *it;
                    l++;
                } else if (mode == 2) {
                    auto it = s.begin();
                    s.erase(it);
                    p[r] = *it;
                    r--;
                } else if (mode == 3) {
                    auto it = s.begin();
                    s.erase(it);
                    p[l] = *it;
                    l++;
                }


                mode = (mode + 1) % 4;
            }

            print(p);
            continue;
        }

        for (int i = n; i > 0; i -= 2) {
            p[i] = i;
            s.erase(i);
        }

        for (int i = n - 1; i > 0; i -= 2) {
            if (i + i+1 <= x) {
                // kraj
                while (i > 0) {
                    if (p[i] == 0) {
                        p[i] = i;
                    }
                    i--;
                }
                break;
            }
            else if (p[i] == 0) {
                auto k = *s.begin();
                p[i] = k;
                p[k] = i;
                s.erase(*s.begin());
                s.erase(i);
            }
        }

        print(p);
    }
    return 0;
}
