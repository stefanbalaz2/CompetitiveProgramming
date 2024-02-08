#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxk=12;
const int maxn=5e4;

set<pii>minedge[maxk][maxk];
int adj[maxk][maxn],k,n,flow[maxk],cap[maxk];

void add_edge(int u,int v){

    ///printf("%d %d ADD\n",u,v);

    /// prvo skini
    for(int i=0;i<k;i++)
        minedge[i][k].erase({adj[i][v],v});
    for(int i=0;i<k;i++){
        if(i==u)continue;
        minedge[i][u].insert({adj[i][v]-adj[u][v],v});
    }
    flow[u]++;
}
void remove_edge(int u,int v){

    ///printf("%d %d REM\n",u,v);

    flow[u]--;
    for(int i=0;i<k;i++){
        if(i==u)continue;
        minedge[i][u].erase({adj[i][v]-adj[u][v],v});
    }
    for(int i=0;i<k;i++)
        minedge[i][k].insert({adj[i][v],v});

}

vector<pair<pii,pll>> g;
void make_graph(){

    g.clear();
    ll inf=1e18;
    for(int i=0;i<k;i++){
        g.pb({{k+1,i},{0,0} });
        for(int j=0;j<k+1;j++){
            pll pom={inf,-1};
            //printf("%d %d %d\n",i,j,minedge[i][j].size());
            if(minedge[i][j].size()){
                pom.ff=(*minedge[i][j].begin()).ff;
                pom.ss=(*minedge[i][j].begin()).ss;
                g.pb({{i,j},pom});
                ///printf("%d %d | %lld %lld AAA\n",i,j,pom.ff,pom.ss);
            }
            //g[i][j]=pom;
        }
    }
    g.pb({ {k,k+2},{0,0} });

}
ll go_flow(){

    make_graph();

    ll inf=1e18;
    vector<ll>dist(k+3,inf);
    vector<int>p(k+3,-1);
    dist[k+1]=0;
    p[k+1]=-1;
    for(int i=0;i<k+3;i++){
        for(int j=0;j<g.size();j++){
            int u=g[j].ff.ff;
            int v=g[j].ff.ss;
            ll w=g[j].ss.ff;

            if(u==k+1){
                if(flow[v]==cap[v])continue;
            }

            if(dist[v]>dist[u]+w){
                p[v]=j;
                dist[v]=dist[u]+w;
                ///printf("%d %d | %lld %lld AA\n",u,v,dist[v],w);
            }

        }
    }

    vector<int>edges;
    int curr=k+2;
    if(p[curr]==-1){
        printf("AAAA\n");
    }
    while(curr!=k+1){
        edges.pb(p[curr]);
        curr=g[p[curr]].ff.ff;
    }

    reverse(edges.begin(),edges.end());
    for(int i=0;i<edges.size();i++){
        ////printf("%d %d %d %d EDGE\n",g[edges[i]].ff.ff,g[edges[i]].ff.ss,g[edges[i]].ss.ss,i);
    }

    for(int i=edges.size()-3;i>0;i-=1){
        int id=edges[i];
       // printf("%d REM\n",i);
        //printf("%d %d %d EDGE222\n",g[edges[i]].ff.ff,g[edges[i]].ff.ss,g[edges[i]].ss.ss);
        remove_edge(g[id].ff.ss,g[id].ss.ss);
    }
    add_edge(g[edges[edges.size()-2]].ff.ff,g[edges[edges.size()-2]].ss.ss);
    ///printf("DOSO\n");
    for(int i=edges.size()-3;i>0;i-=1){
        int id=edges[i];
        add_edge(g[id].ff.ff,g[id].ss.ss);
    }

    ///printf("%lld AAA\n\n\n",dist[k+2]);
    return dist[k+2];
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);

    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            scanf("%d",&adj[j][i]);
            ///printf("%d");
            minedge[j][k].insert({adj[j][i],i});
        }
    }
    for(int i=0;i<k;i++)scanf("%d",&cap[i]);

    ll rez=0;
    for(int i=1;i<=n;i++){
        ///printf("poceo\n");
        rez+=go_flow();
        ///break;
    }

    printf("%lld\n",rez);

    return 0;
}
