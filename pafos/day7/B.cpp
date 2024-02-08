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

const int maxn=5010;
int delta=maxn;
int dp[maxn][2*maxn],l[maxn],r[maxn],cnt[maxn],tmp[2*maxn];
int n,m;
int inf=1e9;
vector<pair<int,pii>>vect[maxn];

void mrg(int &l1,int &r1,int *dp1,int l2,int r2,int *dp2,int flag,int w){

    for(int i=0;i<2*maxn;i++)tmp[i]=inf;

    ///printf("\n");
    for(int j=l2;j<=r2;j++){
        int pom=0;
        if( (abs(j-delta)&1)!=flag)pom=-1;
        int pom2=(abs(j-delta)-pom)*w;

        for(int i=l1;i<=r1;i++){
            tmp[i+j+pom-delta]=min(tmp[i+j+pom-delta],dp1[i]+dp2[j]+pom2);
        }

    }

    l1+=l2-delta;
    l1--;
    r1+=r2-delta;

    for(int i=l1;i<=r1;i++)dp1[i]=tmp[i];

    int mn=inf;
    for(int i=r1;i>=delta;i--){
        mn=min(mn,dp1[i]);
        dp1[i]=min(dp1[i],mn);
    }
}
void go(int x){

    l[x]=delta;
    r[x]=delta+cnt[x];
    for(int i=0;i<=cnt[x];i++)dp[x][delta+i]=0;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        go(id);
        mrg(l[x],r[x],dp[x],l[id],r[id],dp[id],vect[x][i].ss.ss,vect[x][i].ss.ff);
    }

    /*printf("\n%d | %d %d LR\n",x,l[x],r[x]);
    for(int i=l[x];i<=r[x];i++){
        printf("%d %d | %d\n",i-delta,dp[x][i],x);
    }*/

}

int main(){

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d %d",&n,&m);
        for(int i=1;i<=n;i++){
            cnt[i]=0;
            vect[i].clear();
            for(int j=0;j<2*maxn;j++)dp[i][j]=inf;
        }
        for(int i=1;i<n;i++){
            int u,v,w,c;
            scanf("%d %d %d %d",&u,&v,&w,&c);
            vect[u].pb({v,{w,c}});
        }
        for(int i=1;i<=m;i++){
            int a;
            scanf("%d",&a);
            cnt[a]++;
        }

        go(1);

        int rez=inf;
        for(int i=delta;i<2*maxn;i++){
            rez=min(rez,dp[1][i]);
        }
        if(rez==inf)printf("-1\n");
        else printf("%d\n",rez);

    }

    return 0;
}
