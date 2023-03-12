/*

    idea:	https://github.com/farmerboy95/CompetitiveProgramming/blob/master/LiveArchive/LIVEARCHIVE%207172.cpp

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,ll> pii;
const int maxn=1010;
const int maxk=110;
int sz[maxn],k,n;
ll dp[maxn][maxk];
vector<pii>vect[maxn];
void dfs(int x,int prv){
    sz[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        dfs(id,x);
        sz[x]+=sz[id];
    }
}
void go(int x,int prv){

    ll dp2[k+10],dp3[k+10];
    memset(dp2,-1,sizeof(dp2));
    memset(dp3,-1,sizeof(dp3));

    dp2[0]=0;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        ll w=vect[x][i].ss;
        go(id,x);

        for(int kn=0;kn<=min(sz[id],k);kn++){
            if(dp[id][kn]==-1)continue;

            ll cost=min(kn,k-kn+1)*2*w+dp[id][kn];

            for(int j=0;j<=min(sz[x],k);j++){
                if(j+kn>min(sz[x],k))break;
                if(dp2[j]==-1)continue;

                dp3[j+kn]=max(dp3[j+kn],dp2[j]+cost);
            }

        }

        for(int j=0;j<=k;j++){
            dp2[j]=max(dp2[j],dp3[j]);
            dp3[j]=-1;
        }
    }

    for(int i=0;i<=k;i++)dp[x][i]=dp2[i];

    for(int i=k;i>=1;i--)/// adding the subtree root node(only possible when x!=tree_root)
        if(x!=1)dp[x][i]=max(dp[x][i],dp[x][i-1]);

}
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    int po=0;
    while(t--){

        po++;

        scanf("%d %d",&n,&k);
        for(int i=1;i<=n;i++)vect[i].clear();

        for(int i=2;i<=n;i++){
            int p;
            ll c;
            scanf("%d %lld",&p,&c);
            vect[p].pb({i,c});
        }

        memset(dp,-1,sizeof(dp));
        dfs(1,0);
        go(1,0);

        printf("Case %d: ",po);
        printf("%lld\n",max(dp[1][k],0ll));
    }

	return 0;
}
