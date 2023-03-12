#include<bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
ll mod=998244353;
const int maxk=310;
const int maxn=2e5+10;
ll inv[maxk],fact[maxk],powsum[maxk*2],coef[maxk][maxk],a[maxn];
int n,k;
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }
    return ret;
}
ll c(int n,int k){

    ll ret=1;
    ret=fact[n];
    ret=(ret*inv[k])%mod;
    ret=(ret*inv[n-k])%mod;
    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d",&n,&k);


    fact[0]=1;
    inv[0]=1;
    for(ll i=1;i<=k;i++){
        fact[i]=(fact[i-1]*i)%mod;
        inv[i]=step(fact[i],mod-2);
    }

    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        powsum[0]++;
    }

    for(ll i=1;i<=n;i++){

        ll curr=1;
        for(ll j=1;j<=2*k;j++){
            curr=(curr*a[i])%mod;
            powsum[j]=(powsum[j]+curr)%mod;
        }

    }


    for(int i=0;i<=k;i++){
        for(int j=0;j<=k;j++){
            coef[i][j]=(powsum[i]*powsum[j])%mod;
            coef[i][j]=(coef[i][j]-powsum[i+j]+mod)%mod;
        }
    }

    for(int i=1;i<=k;i++){
        ll rez=0;
        for(int j=0;j<=i/2;j++)
            rez=(rez+c(i,j)*coef[j][i-j])%mod;

        if(i%2==0)rez=(rez-(((c(i,i/2)*coef[i/2][i-i/2])%mod)*inv[2])%mod +mod)%mod;

        printf("%lld\n",rez);
    }


return 0;
}
