/*

    idea: https://github.com/ryuzmukhametov/CompetitiveProgramming/blob/master/spoj/SPOJ%20EASYFACT.cpp

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
const int maxn=1e8;
bool pos[maxn+10];
ll primes[maxn/10];
int br;
ll mod;
void sito(){

    for(int i=2;i<=maxn;i++){
        if(pos[i])continue;
        primes[++br]=i;

        for(int j=i;j<=maxn;j+=i)pos[j]=1;
    }
}
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;
        base=(base*base)%mod;

        pw/=2;
    }

    return ret;
}
ll go(int n){

    ll j;
    ll ret=1;
    for(j=2;primes[j]*primes[j]<=(ll)n;j++){

        ll pom=primes[j];
        ll cnt=0;
        ll pom2=pom;

        while(pom2<=n){
            cnt+=n/pom2;
            pom2*=pom;
        }

        ret=(ret*(cnt+1))%mod;

    }

    int lp=j;
    int rp=br;
    while(1){

        if(n/primes[lp]==0)break;

        int l=lp;
        int r=rp;
        int sr,ret2;
        while(l<=r){
            sr=(l+r)/2;
            if(n/primes[sr]==n/primes[lp]){
                ret2=sr;
                l=sr+1;
            }
            else r=sr-1;
        }

        ret=(ret*step(n/primes[lp]+1,ret2-lp+1))%mod;

        lp=ret2+1;
    }

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);

    sito();

    int t;
    scanf("%d",&t);
    while(t--){

        int n;
        scanf("%d %lld",&n,&mod);
        ll ret=go(n);
        ret--;
        if(ret<0)ret+=mod;
        printf("%lld\n",ret);
    }

	return 0;
}
