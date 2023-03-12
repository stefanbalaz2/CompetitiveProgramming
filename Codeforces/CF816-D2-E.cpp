/*

    idea: https://codeforces.com/blog/entry/52742

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=5010;
vector<ll>dp[2][maxn];
vector<int>vect[maxn];
ll c[maxn],d[maxn],b,inf=1e18;
int sz[maxn],n;
void go_sz(int x){

    sz[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        go_sz(id);
        sz[x]+=sz[id];
    }
}
void go(int x){
//
    dp[1][x].resize(sz[x]+1);
    dp[0][x].resize(sz[x]+1);
    fill(dp[1][x].begin(),dp[1][x].end(),inf);
    fill(dp[0][x].begin(),dp[0][x].end(),inf);

    dp[0][x][0]=0;
    dp[0][x][1]=c[x];
    dp[1][x][0]=0;
    dp[1][x][1]=c[x]-d[x];

    int pom=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        go(id);

        for(int j=pom;j>=1;j--){
            for(int k=sz[id];k>=1;k--){
                if(dp[1][x][j]==inf)continue;
                dp[1][x][j+k]=min(dp[1][x][j+k],dp[1][x][j]+dp[0][id][k]);
                dp[1][x][j+k]=min(dp[1][x][j+k],dp[1][x][j]+dp[1][id][k]);
            }
        }

        for(int j=pom;j>=0;j--){
            for(int k=sz[id];k>=1;k--){
                if(dp[0][x][j]==inf)continue;
                dp[0][x][j+k]=min(dp[0][x][j+k],dp[0][x][j]+dp[0][id][k]);
            }
        }

        pom+=sz[id];
    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d %lld",&n,&b);
    for(int i=1;i<=n;i++){

        scanf("%lld %lld",&c[i],&d[i]);
        if(i>1){
            int u;
            scanf("%d",&u);
            vect[u].pb(i);
        }

    }

    go_sz(1);
    go(1);

    for(int i=n;i>=0;i--){
        if(dp[0][1][i]<=b || dp[1][1][i]<=b){
            printf("%d\n",i);
            return 0;
        }
    }

	return 0;
}
