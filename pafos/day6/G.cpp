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

const int maxb=62;
const int maxn=64;

int dp[maxb+1][(maxb+1)*maxn];
int n,niz[maxb+1];
ll s;
int fact[maxn],inv[maxn];
int c(int n,int k){
    if(n<0 || k<0 || n<k)return 0;
    return mul(fact[n],mul(inv[k],inv[n-k]));
}

int go(int i,int m){

    if(i==-1)return 1;
    m=min(m,(maxb+1)*maxn-1);
    if(dp[i][m]!=-1)return dp[i][m];

    int &a=dp[i][m];
    a=0;

    int mx=min(n,min(i+1,m));

    int ns=0;
    if(i>0)ns=niz[i-1];

    for(int k=0;k<=mx;k++)
        a=add(a,mul(go(i-1,(m-k)*2+ns),c( min(n,i+1),k ) ));

    ///printf("%d");

    return a;
}

int main(){

    memset(dp,-1,sizeof(dp));

    fact[0]=inv[0]=1;
    for(int i=1;i<maxn;i++)fact[i]=mul(fact[i-1],i);
    inv[maxn-1]=invv(fact[maxn-1]);
    for(int i=maxn-1;i>0;i--)inv[i-1]=mul(inv[i],i);

    scanf("%d %lld",&n,&s);
    s-=((1ll)<<(n-1));

    if(s<0){
        printf("0\n");
        return 0;
    }

    for(int i=maxb-1;i>=0;i--)
        if((1ll<<i)&s)niz[i]=1;

    ///printf("%lld SS\n",s);

    printf("%d\n",go(maxb,0));

    return 0;
}
