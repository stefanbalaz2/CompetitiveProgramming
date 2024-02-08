#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<pair<int, int>> vpii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int MAXN = 200010;
pii a[MAXN], b[MAXN];
ll pref_a[MAXN], pref_b[MAXN];
int n, m;

ll dp_val1[MAXN]; // Stays too far such that there is at least one B in between.
ll dp_val2[MAXN]; // Stays too far but there might not be a B in between.
ll dp_val3[MAXN]; // Stands too close so that the intervals intersect.

ll DP[MAXN][2]; // DP[i][0/1] -- taking A[i], clearing to the left (including), 0/1 if some B has already been taken.


ll get_pref_b (int val) {
    int ans = -1;
    int lo = 0, hi = m - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (b[mid].first <= val) {
            ans = mid;
            lo = mid + 1;
        } else {
    `       hi = mid - 1;
        }
    }
    if (ans == -1) return 0;
    return pref_b[ans];
}


ll get_far (int i, int p, ll dp_val) {
    return dp_val
        + get_pref_b(a[i].first + p - 1) - get_pref_b(a[i].first)
        - pref_a[i - 1];
}

ll get_close (int i, int p, ll dp_val) {
    return dp_val
        - get_pref_b(a[i].first)
        - pref_a[i - 1];
}

void check (ll p) {
    // I want to do DP on A.
    DP[0][0] = 0;
    DP[0][1] = LONG_LONG_MIN;

    // int g1 = 0, g2 = 0;
    vector<int> group(n + 1, 3);
    // groups are supposed to be 1/2/3
    multiset<int> dp_get[3][2];
    for (int i = 1; i <= n; i++) {
        // First option: this is the first one we are taking.
        ll deleteACost = pref_a[i - 1];
        ll deleteBCost = get_pref_b(a[i].first) - get_pref_b(a[i].first - p);
        bool leavesB = get_pref_b(a[i].first - p) > 0;
        if (leavesB) {
            DP[i][1] = DP[i][0] = deleteACost + deleteBCost;
        } else {
            DP[i][0] = deleteACost + deleteBCost;
            DP[i][1] = LONG_LONG_MIN;
        }

        ll new_bnd = a[i].first - 2 * p + 1;
        // Second option: we are taking some j previously.

        while (a[g2].first < new_bnd) {
            // We should move g2 to the right.
            // So remove g2 from the group it was in previously
            assert (group[g2] != 2);
            if (group[g2] != 3) {
                dp_get[group[g2]][0].erase(dp_get[group[g2]].find(get_far(g2, p, DP[g2][0])));
                dp_get[group[g2]][1].erase(dp_get[group[g2]].find(get_far(g2, p, DP[g2][1])));
            }
            dp_get[2][0].insert(get_close(g2, p, DP[g2][0]));
            dp_get[2][1].insert(get_close(g2, p, DP[g2][1]));
            group[g2] = 2;
        }


    }
}

void solve() {
    scanf("%d %d", &n, &m);
    ll s; scanf("%lld", &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i].first);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].second);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i].second);
    }
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= n; i++) {
        pref_a[i] = pref_a[i - 1] + a[i].second;
    }
    for (int i = 1; i <= m; i++) {
        pref_b[i] = pref_b[i - 1] + b[i].second;
    }
    int lo = 1, hi = 2e9 + 5;
    int ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    assert (ans != -1);
    printf("%d\n", ans);
}

int main(){
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}
