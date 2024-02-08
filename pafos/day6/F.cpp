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

typedef pair<ll, ll> frac;

bool is_less (frac a, frac b) {
    return a.first * b.second < b.first * a.second;
}

int main(){
    int n, x, k;
    scanf("%d %d %d", &n, &x, &k);
    vector<int> spins(k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &spins[i]);
    }
    vector<int> dist(n, -1);
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int top = q.front();
        q.pop();
        for (int i = 0; i < k; i++) {
            int ni = (top - spins[i] + n) % n;
            if (dist[ni] == -1) {
                dist[ni] = 1 + dist[top];
                q.push(ni);
            }
        }
    }

    vector<int> cnt(n + 1, 0);
    int infs = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) infs += 1;
        else cnt[dist[i]] += 1;
    }

    // all > bnd
    frac ans;
    if (dist[x] != -1) ans = {dist[x], 1};
    else ans = {INT_MAX, 1};

    ll cnt_smaller = 0; ll sum_smaller = 0;
    for (int bnd = 0; bnd <= n; bnd++) {
        cnt_smaller += cnt[bnd];
        sum_smaller += 1ll * bnd * cnt[bnd];

        frac attempt = {n + sum_smaller, cnt_smaller};
        if (cnt_smaller != 0) {
            if (is_less(attempt, ans)) ans = attempt;
        }
    }

    ll g = __gcd(ans.first, ans.second);
    ans.first /= g;
    ans.second /= g;

    printf("%lld %lld\n", ans.first, ans.second);
    return 0;
}
