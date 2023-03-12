/*

    idea:https://codeforces.com/blog/entry/68405

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxn=2e5+10;
ll fact[maxn],inv2[maxn],invf[maxn],T,rez,mod=1e9+7;
int n;
ll c(int n,int k){

    ll ret=fact[n];
    ret=(ret*invf[n-k])%mod;
    ret=(ret*invf[k])%mod;

    return ret;
}
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw>>=1;
    }

    return ret;
}
int main(){

    scanf("%d %lld",&n,&T);

    fact[0]=1;
    inv2[0]=1;
    invf[0]=1;
    for(int i=1;i<=n+5;i++){
        fact[i]=(fact[i-1]*i)%mod;
        inv2[i]=step(step(2,i),mod-2);
        invf[i]=step(fact[i],mod-2);
    }

    ll cs=0;
    ll cp=1;
    ll prvk=0;
    for(int i=1;i<=n;i++){
        ll a;
        scanf("%lld",&a);

        cs+=a;
        ll id=min(T,cs+i)-cs;
        if(id<0)break;

        cp*=2;
        cp%=mod;
        if(id!=i){
            cp-=c(i-1,prvk);
            cp%=mod;
            if(cp<0)cp+=mod;

            for(int j=prvk;j>id;j--){
                cp-=c(i,j);
                cp%=mod;
                if(cp<0)cp+=mod;
            }
        }

        rez+=(cp*inv2[i])%mod;
        rez%=mod;

        prvk=id;
    }


    printf("%lld\n",rez);

    return 0;
}
