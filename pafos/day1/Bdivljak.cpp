#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;


const int maxn=9;
const int maxm=65;
const int maxa=5e4;
ll dp[maxa][(1<<maxn)];
ll n,m[maxn],len[maxn],xp[maxn][maxm],yp[maxn][maxm];
ll inf=1e16;
ll get_func_cost(int x,ll pos){

    ///printf("%d %lld CALC\n",x,pos);

    if(pos<xp[x][0] || pos>xp[x][m[x]-1])return inf;
    for(int j=1;j<m[x];j++){

        //if((yp[x][j]-yp[x][j-1])%(xp[x][j]-xp[x][j-1])==0){}
        //else printf(" AAA\n");

        if(pos<=xp[x][j] && pos>=xp[x][j-1]){
            return (pos-xp[x][j-1])*((yp[x][j]-yp[x][j-1])/(xp[x][j]-xp[x][j-1]))+yp[x][j-1];
        }
    }

    return yp[x][0];
}

int main(){

    freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%lld",&n);

    for(int i=0;i<n;i++){

        scanf("%lld %lld",&m[i],&len[i]);

        for(int j=0;j<m[i];j++){
            scanf("%lld %lld",&xp[i][j],&yp[i][j]);
        }
    }

    ///printf("%lld AA\n",get_func_cost(2,544));

    ll rez=inf;

    for(int i=0;i<maxa;i++)
        for(int mask=0;mask<(1<<n);mask++)
            dp[i][mask]=inf;

    for(int i=0;i<maxa;i++)dp[i][0]=0;
    for(int i=0;i<maxa;i++){

        for(int mask=0;mask<(1<<n);mask++){

            if(i>0)dp[i][mask]=min(dp[i][mask],dp[i-1][mask]);

            for(int j=0;j<n;j++){
                if((1<<j)&mask){
                    ///if(i-len[j]>=0)printf("%d %lld %lld COST\n",j,get_func_cost(j,i-len[j]),dp[i-len[j]][mask^(1<<j)]);
                    if(i-len[j]>=0)dp[i][mask]=min(dp[i][mask],dp[i-len[j]][mask^(1<<j)]+get_func_cost(j,i-len[j]));
                }

            }

            if(mask==(1<<n)-1){
                rez=min(rez,dp[i][mask]);
            }

            ///if(dp[i][mask]!=inf)printf("%d %d | %lld AA\n",i,mask,dp[i][mask]);

        }

    }

    printf("%lld\n",rez);

    return 0;
}
