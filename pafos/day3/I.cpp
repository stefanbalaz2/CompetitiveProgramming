#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef long long ll;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int MAXN = 500010;
int a[MAXN], run[MAXN], cnt[MAXN], cnt_larger[MAXN];
ll sum_cnt_larger[MAXN];

ll c2 (int x) {
    return (ll) x * (x - 1) / 2;
}

vector<int> occ[MAXN];
ll ans[MAXN];

void process (const vector<int> &v) {
    // printf("processing...\n");
    int n = (int)v.size();
    vector<int> run(n), cnt(n + 1, 0);
    run[n - 1] = 1; cnt[1] += 1;
    for (int i = n - 2; i >= 0; i--) {
        if (v[i] + 1 == v[i + 1]) {
            run[i] = run[i + 1] + 1;
        } else {
            run[i] = 1;
        }
        cnt[run[i]] += 1;
    }
    int max_run = *max_element(run.begin(), run.end());
    // printf("max run is %d\n", max_run);
    vector<int> cnt_larger(max_run + 1, 0);
    vector<ll> sum_cnt_larger(max_run + 1, 0);
    cnt_larger[max_run] = sum_cnt_larger[max_run] = cnt[max_run];
    for (int i = max_run - 1; i >= 1; i--) {
        cnt_larger[i] = cnt_larger[i + 1] + cnt[i];
        sum_cnt_larger[i] = sum_cnt_larger[i + 1] + cnt_larger[i];
    }
    /*for (int i = 1; i <= max_run; i++) {
        printf("%d ", cnt_larger[i]);
    }
    printf("\n");*/
    for (int k = 1; k <= max_run; k++) {
        ll total = c2(cnt_larger[k]);
        total -= (k + 1 <= max_run ? sum_cnt_larger[k + 1] : 0);
        total += (2 * k <= max_run ? sum_cnt_larger[2 * k] : 0);
        ans[k] += total;
    }
}

void solve() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        occ[i].clear();
        ans[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        occ[a[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        // printf("CURR %d\n", i);
        if (!occ[i].empty()) {
            process(occ[i]);
        }
    }
    for (int i = 1; i <= n / 2; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
}
int main(){
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}
