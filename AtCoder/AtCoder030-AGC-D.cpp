/*

    idea: https://img.atcoder.jp/agc030/editorial.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=3010;
int n,q,a[maxn];
ll mod=1e9+7;
ll dp[maxn][maxn][3],dp2[maxn][maxn][3],q2;

ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;
    }

return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            dp[i][j][0]=(a[i]<a[j]);
            dp[i][j][1]=(a[i]==a[j]);
            dp[i][j][2]=(a[i]>a[j]);
        }
    }

    ll inv2=step(2,mod-2);

    q2=1;
    while(q--){

        q2=(q2*2)%mod;

        int l,r;
        scanf("%d %d",&l,&r);
        if(l>r)swap(l,r);

        /// UPTO L
        for(int i=1;i<l;i++){
            ll pom0=dp[i][l][0];
            ll pom1=dp[i][l][1];
            ll pom2=dp[i][l][2];

            dp[i][l][0]=(inv2*dp[i][l][0]+inv2*dp[i][r][0])%mod;
            dp[i][l][1]=(inv2*dp[i][l][1]+inv2*dp[i][r][1])%mod;
            dp[i][l][2]=(inv2*dp[i][l][2]+inv2*dp[i][r][2])%mod;

            dp[i][r][0]=(inv2*dp[i][r][0]+inv2*pom0)%mod;
            dp[i][r][1]=(inv2*dp[i][r][1]+inv2*pom1)%mod;
            dp[i][r][2]=(inv2*dp[i][r][2]+inv2*pom2)%mod;
        }

        /// L
        for(int i=l+1;i<=n;i++){

            dp2[l][i][0]=dp[l][i][0];
            dp2[l][i][1]=dp[l][i][1];
            dp2[l][i][2]=dp[l][i][2];

            if(i<r){
                dp[l][i][0]=(inv2*dp[l][i][0]+inv2*dp[i][r][2])%mod;
                dp[l][i][1]=(inv2*dp[l][i][1]+inv2*dp[i][r][1])%mod;
                dp[l][i][2]=(inv2*dp[l][i][2]+inv2*dp[i][r][0])%mod;
            }
            else if(i==r){
                ll pom=dp[l][i][0];
                dp[l][i][0]=(inv2*dp[l][i][0]+inv2*dp[l][i][2])%mod;
                dp[l][i][1]=(inv2*dp[l][i][1]+inv2*dp[l][i][1])%mod;
                dp[l][i][2]=(inv2*dp[l][i][2]+inv2*pom)%mod;
            }
            else{
                dp[l][i][0]=(inv2*dp[l][i][0]+inv2*dp[r][i][0])%mod;
                dp[l][i][1]=(inv2*dp[l][i][1]+inv2*dp[r][i][1])%mod;
                dp[l][i][2]=(inv2*dp[l][i][2]+inv2*dp[r][i][2])%mod;
            }

        }

        /// L to R
        for(int i=l+1;i<r;i++){
            dp[i][r][0]=(inv2*dp[i][r][0]+inv2*dp2[l][i][2])%mod;
            dp[i][r][1]=(inv2*dp[i][r][1]+inv2*dp2[l][i][1])%mod;
            dp[i][r][2]=(inv2*dp[i][r][2]+inv2*dp2[l][i][0])%mod;
        }

        /// R
        for(int i=r+1;i<=n;i++){
            dp[r][i][0]=(inv2*dp[r][i][0]+inv2*dp2[l][i][0])%mod;
            dp[r][i][1]=(inv2*dp[r][i][1]+inv2*dp2[l][i][1])%mod;
            dp[r][i][2]=(inv2*dp[r][i][2]+inv2*dp2[l][i][2])%mod;
        }

    }

    ll rez=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            rez+=(dp[i][j][2]*q2);
            rez%=mod;
        }
    }

    printf("%lld\n",rez);

	return 0;
}
