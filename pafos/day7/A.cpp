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

vector<ll> prefix (const vector<int> &a) {
    int n = (int)a.size() - 1;
    vector<ll> ret(n + 1, 0);
    ret[0] = 0;
    for (int i = 1; i <= n; i++) {
        ret[i] = ret[i - 1] + a[i];
    }
    return ret;
}
void solve() {
    int n; scanf("%d", &n);
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    if (n == 1) {
        printf("%d\n", a[1]);
        return;
    }
    if (n == 2) {
        printf("%d\n", a[1] + max(a[2], b[1]));
        return;
    }
    vector<ll> pref_a = prefix(a), pref_b = prefix(b);
    ll ans = 0;
    if (n % 2 == 1) {
        // ja gore on dole
        ans = max(ans, pref_a[n / 2 + 1] + min(pref_a[n] - pref_a[n / 2 + 1], pref_b[n / 2 + 1]));

        // ja dole on dole
        ll safe = pref_a[n / 2] + pref_b[n / 2];

        // ja dole on gore
        // ll bot2 = max(safe, a[1] + pref_b[n / 2 + 1] + min(pref_b[n - 1] - pref_b[n / 2 + 1], pref_a[n / 2 + 1] - pref_a[1]));

        ans = max(ans, safe);
    } else {
        // ja gore on dole
        ans = max(ans, pref_a[n / 2 + 1] + min(pref_a[n] - pref_a[n / 2 + 1], pref_b[n / 2 + 1]));

        // ja dole on dole
        ll safe = pref_a[n / 2] + pref_b[n / 2];

        ans = max(ans, safe);
    }

    printf("%lld\n", ans);
}

int main(){
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}
