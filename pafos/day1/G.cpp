#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

int ask (ll x) {
    printf("query %lld\n", x);
    fflush(stdout);
    int ret; scanf("%d", &ret);
    return ret;
}

int main(){
    int sum_x = ask(0);
    ll mult = 1;
    ll answer = 0;
    int sum_answer = 0;
    for (int dig = 0; dig < 18 && sum_answer < sum_x; dig++) {
        int lo = 0, hi = 9, ans = 0;
        while (lo <= hi) {
            int m_small = (lo + hi) / 2;
            ll to_ask = (10 - m_small) * mult;
            int got = ask(to_ask);
            if (got < sum_x + (10 - m_small)) {
                // prekoracio
                // cifra >= 10 - got
                // cifra >= m_small
                ans = m_small;
                lo = m_small + 1;
            } else {
                hi = m_small - 1;
            }
        }
        fprintf(stderr, "pos %d found %d\n", dig, ans);
        answer += ans * mult;
        sum_answer += ans;
        mult *= 10;
    }
    printf("answer %lld\n", answer);
    return 0;
}
