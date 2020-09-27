/*

    idea: https://img.atcoder.jp/agc043/editorial.pdf

*/
#include<bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll> pii;
const int maxn=2010;
const int offset=3*maxn;
int n,dp[maxn*3][6*maxn];
ll mod;
int main(){

   /// freopen("test.txt","r",stdin);

    scanf("%d %lld",&n,&mod);

    dp[0][offset]=1;
    for(int i=0;i<=n*3;i++){
        for(int j=0;j<=offset*2;j++){

            if(dp[i][j]==0)continue;

            dp[i+1][j+1]+=dp[i][j];
            if(dp[i+1][j+1]>=mod)dp[i+1][j+1]-=mod;

            dp[i+2][j-1]+=((ll)dp[i][j]*(ll)(i+1))%mod;
            if(dp[i+2][j-1]>=mod)dp[i+2][j-1]-=mod;

            dp[i+3][j]+=((ll)dp[i][j]*(ll)(i+1)*(ll)(i+2))%mod;
            if(dp[i+3][j]>=mod)dp[i+3][j]-=mod;

        }
    }

    ll rez=0;
    for(int i=offset;i<=offset+3*n;i++)
        rez=(rez+(ll)dp[n*3][i])%mod;

    printf("%lld\n",rez);


return 0;
}
