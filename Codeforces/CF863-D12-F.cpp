/*

    idea: mincost flow

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=50*50+100;
int source,sink,dp[maxn],p[maxn],inf=1e9,pot[maxn],n,q,mn[maxn],mx[maxn],cnt,ind[maxn][maxn];
struct edge{
    int a,b,flow,cost;
};
vector<edge>e;
vector<int>vect[maxn];
void add_edge(int x,int y,int cost){

    vect[x].pb(e.size());
    e.pb({x,y,0,cost});

    vect[y].pb(e.size());
    e.pb({y,x,1,-cost});
}
int go(){

    set<pii>st;
    st.insert({0,source});
    fill(dp,dp+sink+1,inf);
    memset(p,-1,sizeof(p));
    dp[source]=0;

    while(st.size()){

        int x=(*st.begin()).ss;
        st.erase(st.begin());

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].flow)continue;
            int w=pot[e[id].a]+e[id].cost-pot[e[id].b];

            if(dp[x]+w<dp[e[id].b]){
                st.erase({dp[e[id].b],e[id].b});
                dp[e[id].b]=dp[x]+w;
                p[e[id].b]=id;
                st.insert({dp[e[id].b],e[id].b});
            }
        }

    }

    if(p[sink]==-1)return 0;

    int curr=sink;
    int ret=0;
    while(curr!=source){
        e[p[curr]].flow++;
        e[p[curr]^1].flow--;
        ret+=e[p[curr]].cost;
        curr=e[p[curr]].a;
    }

    for(int i=source;i<=sink;i++)pot[i]=dp[i];

    return ret;
}
pii flow_it(){

    pii ret={0,0};

    while(1){

        int cost=go();

        if(cost==0)break;

        ret.ff++;
        ret.ss+=cost;
    }

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&q);

    for(int i=1;i<=n;i++){
        mn[i]=1;
        mx[i]=n;
    }

    for(int i=1;i<=q;i++){

        int tip,l,r,val;
        scanf("%d %d %d %d",&tip,&l,&r,&val);

        if(tip==1)for(int j=l;j<=r;j++)mn[j]=max(mn[j],val);
        else for(int j=l;j<=r;j++)mx[j]=min(mx[j],val);
    }

    cnt=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ind[i][j]=++cnt;
        }
    }
    source=0;
    sink=cnt+1;

    for(int i=1;i<=n;i++){
        if(mn[i]>mx[i]){
            printf("-1\n");
            return 0;
        }

        for(int j=mn[i];j<=mx[i];j++)
            for(int k=1;k<=n;k++)
                add_edge(i,ind[j][k],k*k-((k-1)*(k-1)));

    }
    for(int i=1;i<=n;i++)add_edge(source,i,0);
    for(int i=n+1;i<sink;i++)add_edge(i,sink,0);

    pii rez=flow_it();

    if(rez.ff<n){
        printf("-1\n");
        return 0;
    }

    printf("%d\n",rez.ss);

    return 0;
}
