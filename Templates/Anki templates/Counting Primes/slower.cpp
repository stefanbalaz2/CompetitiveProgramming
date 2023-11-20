/**

  O(n^(3/4))
  https://judge.yosupo.jp/problem/counting_primes

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=3e5+10;

ll calc_primes(ll n){

    vector<ll>m;
    for(ll i=1;i*i<=n;i++){
        m.pb(i);
        m.pb(n/i);
    }
    sort(m.begin(),m.end());
    m.resize(unique(m.begin(),m.end())-m.begin());

    ll sq=sqrt(n);

    auto geti=[&](ll x){
        if(x<=sq)return x-1;
        return (int)m.size()-n/x;
    };

    vector<ll>dp(m.size());

    for(int i=0;i<dp.size();i++)
        dp[i]=m[i];

    ll a=0;
    for(ll p=2;p*p<=n;p++){

        if(dp[geti(p)]!=dp[geti(p-1)]){
            a++;
            for(ll j=m.size()-1;j>0;j--){
                if(p*p>m[j])break;
                dp[j]-=dp[geti(m[j]/p)]-a;
            }
        }

    }

    return dp[geti(n)]-1;
}

int main(){


    ///freopen("test.txt","r",stdin);

    ll n;
    scanf("%lld",&n);
    printf("%lld\n",calc_primes(n));

    return 0;
}
