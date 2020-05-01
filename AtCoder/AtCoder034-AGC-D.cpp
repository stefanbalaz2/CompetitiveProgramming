/*

    idea: https://img.atcoder.jp/agc034/editorial.pdf

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,int> pii;
const int maxn=2e3+10;
struct edge{
    int a,b,flow,cap;
    ll cost;
};
int parent[maxn],source,sink,mflow,maxflow,n;
ll dp[maxn],pot[maxn],rez;
vector<edge>e;
vector<int>vect[maxn];
int inf=1e9;
ll offset=1e10;
void add_edge(int a,int b,int cap,ll cost){

    cost=-cost;
    cost+=offset;

    vect[a].pb(e.size());
    e.pb({a,b,0,cap,cost});

    vect[b].pb(e.size());
    e.pb({b,a,cap,cap,-cost});
}
ll flow(){

    memset(parent,-1,sizeof(parent));
    for(int i=source;i<=sink+4;i++)dp[i]=1e18;

    set<pii>st;
    st.insert({0,source});
    dp[source]=0;
    while(st.size()){

        int x=(*st.begin()).ss;
        st.erase(st.begin());

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            ll w=pot[x]+e[id].cost-pot[e[id].b];
            if(e[id].flow>=e[id].cap || dp[x]+w>=dp[e[id].b])continue;

            int id2=e[id].b;
            st.erase({dp[id2],id2});
            dp[id2]=dp[x]+w;
            parent[id2]=id;
            st.insert({dp[id2],id2});
        }

    }

    for(int i=source;i<=sink+4;i++)pot[i]=dp[i];

    int x=sink;
    int flow=1e9;
    while(x!=source){
        int id=parent[x];
        flow=min(flow,e[id].cap-e[id].flow);
        x=e[id].a;
    }

    mflow+=flow;

    x=sink;
    ll cost=0;
    while(x!=source){
        int id=parent[x];
        cost+=e[id].cost;
        x=e[id].a;

        e[id].flow+=flow;
        e[id^1].flow-=flow;
    }

    cost-=4*offset;
    cost=-cost;
    cost*=(ll)flow;

    return cost;
}
void go(){

    while(mflow<maxflow)
        rez+=flow();

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    source=0;
    sink=2*n+1;
    for(int i=1;i<=n;i++){
        ll x,y,w;
        scanf("%lld %lld %lld",&x,&y,&w);

        maxflow+=(int)w;

        add_edge(source,i,w,0);
        add_edge(i,sink+1,inf,x+y);
        add_edge(i,sink+2,inf,x-y);
        add_edge(i,sink+3,inf,-x+y);
        add_edge(i,sink+4,inf,-x-y);
    }
    for(int i=1;i<=n;i++){
        ll x,y,w;
        scanf("%lld %lld %lld",&x,&y,&w);

        add_edge(i+n,sink,w,0);
        add_edge(sink+1,i+n,inf,-x-y);
        add_edge(sink+2,i+n,inf,-x+y);
        add_edge(sink+3,i+n,inf,x-y);
        add_edge(sink+4,i+n,inf,x+y);
    }

    go();

    printf("%lld\n",rez);

	return 0;
}
