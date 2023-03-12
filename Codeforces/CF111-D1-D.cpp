/*

    idea:
*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
ll mod=1e9+7;
const int maxk=1e6+10;
const int maxn=1e3+10;
ll fact[maxk],inv[maxk],rez[maxn];
int n,m,k,c[maxn][maxn],dp[maxn],temp[maxn];
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;
    }

    return ret;
}
ll comb(int n,int k){

    ll ret=fact[n];
    ret=(ret*inv[k])%mod;
    ret=(ret*inv[n-k])%mod;

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d %d",&n,&m,&k);

    fact[0]=1;
    inv[0]=1;
    for(int i=1;i<=k;i++){
        fact[i]=((ll)fact[i-1]*(ll)i)%mod;
        inv[i]=step(fact[i],mod-2);
    }

    c[0][0]=1;
    for(int i=1;i<=n;i++){
        c[i][0]=1;
        for(int j=1;j<=n;j++)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }

    dp[0]=1;
    for(int i=0;i<n;i++){

        memset(temp,0,sizeof(temp));

        for(int j=0;j<n;j++){
            if(dp[j]==0)continue;

            for(int k=1;k<=n-j;k++)
                temp[j+k]=((ll)temp[j+k]+(ll)dp[j]*(ll)c[n-j][k])%mod;
        }


        memcpy(dp,temp,sizeof(temp));

        rez[i+1]=dp[n];
        rez[i+1]=((ll)rez[i+1]*inv[i+1])%mod;

    }


    int ret=0;
    for(int i=1;i<=n;i++){
        if(m==1)ret=((ll)ret+ (((ll)rez[i]*comb(k,i))%mod)*fact[i] )%mod;
        else if(m==2)ret=((ll)ret+ (((((ll)rez[i]*comb(k,i))%mod)*fact[i])%mod)*(((((ll)rez[i]*comb(k,i))%mod)*fact[i])%mod) )%mod;
        else{

            for(int j=1;j<=i;j++){
                ret=((ll)ret+ (((((((((((((ll)rez[i]*(ll)rez[i])%mod)*step(j,(m-2)*n))%mod)*comb(k,j))%mod)*comb(k-j,i-j))%mod)*comb(k-j-(i-j),i-j))%mod)*fact[i])%mod)*fact[i] )%mod;
            }

        }
    }

    printf("%d\n",ret);

    return 0;
}
