/*

    a notice: code is not so clean and as fast as it could be, written late at night

    observation: when we place a domino, we disable at most 6 more other moves, meaning,
    only moves that are actually important are the highest 7*(k-1)+1
    because, lets say that we need to take something smaller which is out of that range
    we can always replace that move with a more expensive one in those first 7*(k-1)+1
    because we will always have enough to place k dominoes in those highest 7*(k-1)+1
    moves


    observation 2: we can model this problem as a mincost matching problem, where we iterate upto
    flow of k, augmenting 1 flow every iteration

    so, how do we actually do it? we have costs of moves which sum we want to maximise,
    making a bipartite graph like a chess board, black ones connected to the source and
    the white ones to the sink, and match the neighbouring cells with edges of cost of placing a domino
    on those 2 positions

    next problem: looks like we need maximum cost flow from our constructed graph, how  do we
    convert it to mincost problem? we just multiply edge weights by -1 and we have are then
    looking for a mincost flow.

    next problem: now the initial edges have negative values, we cant let dijkstra deal with that
    we run johnsons algorithm to reweight the edges so dijkstra could be used, after reweighting
    we need to construct the flow graph(the backward-flow edges)

    final problem: now we have constructed a bipartite graph in which we need to find the mincost
    k-flow, all the forward edges are positive in the begining, making it possible to solve it with
    dijkstra(using potentials to evaluate new edge weights) instead of SPFA

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=2000+10;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
struct edge{
    int a,b;
    bool flow;
    int actual_cost,new_cost;
};
vector<edge>e;
vector<int>vect[maxn*maxn];
set<int>mapa2;
set<pair<int,pii> >mapa;
int br,sink,source,n,k,a[maxn][maxn],num[maxn][maxn],pot[maxn*maxn],dp[maxn*maxn],p[maxn*maxn],pos[maxn*maxn],parit[maxn*maxn];
void make_edge(int x,int y,int flow,int cost){

    vect[x].pb(e.size());
    e.pb({x,y,0,cost,0});

    vect[y].pb(e.size());
    e.pb({y,x,flow,-cost,0});
}
void johnson(){

    memset(dp,0,sizeof(dp));
    memset(pos,0,sizeof(pos));

    queue<int>q;
    for(int i=source;i<=sink;i++)q.push(i);

    while(q.size()){

        int x=q.front();
        pos[x]=0;
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=e[vect[x][i]].b;
            int cost=e[vect[x][i]].actual_cost;

            if(e[vect[x][i]].flow)continue;

            if(dp[id]>dp[x]+cost){
                if(!pos[id]){
                    pos[id]=1;
                    q.push(id);
                }
                dp[id]=dp[x]+cost;
            }
        }

    }


    for(int i=0;i<e.size();i++){
        int u=e[i].a;
        int v=e[i].b;

        e[i].new_cost=dp[u]+e[i].actual_cost-dp[v];
    }
}
int dijkstra(){

    for(int i=source;i<=sink;i++)dp[i]=1e9;
    dp[source]=0;

    set<pii>st;
    st.insert({dp[source],source});
    while(st.size()){

        int x=(*st.begin()).ss;
        st.erase(st.begin());

        ///printf("%d A U KURAC\n",x);

        for(int i=0;i<vect[x].size();i++){
            int id=e[vect[x][i]].b;
            if(e[vect[x][i]].flow)continue;

            int cost=pot[x]+e[vect[x][i]].new_cost-pot[id];

            if(dp[id]>dp[x]+cost){
                p[id]=vect[x][i];
                st.erase({dp[id],id});
                dp[id]=dp[x]+cost;
                st.insert({dp[id],id});
            }
        }

    }


    int ret=0;
    int curr=sink;
    while(curr!=source){

        e[p[curr]].flow^=1;
        e[p[curr]^1].flow^=1;

        ret-=e[p[curr]].actual_cost;
        curr=e[p[curr]].a;
    }

    for(int i=source;i<=sink;i++)pot[i]=dp[i];

    return ret;
}
int let_it_flow(){
    return dijkstra();
}
void extract_sufficient_edges(){/// taking the edges that i have chosen as important, and making a bipartite graph out of them

    int kolko=7*k;
    while(kolko--){

        if(mapa.size()==0)break;
        set<pair<int,pii> >::iterator it=mapa.begin();
        int a=(*it).ss.ff;
        int b=(*it).ss.ss;
        int cost=(*it).ff;

        mapa2.insert(a);
        mapa2.insert(b);

        make_edge(a,b,1,cost);

        mapa.erase(mapa.begin());
    }

    for(set<int>::iterator it=mapa2.begin();it!=mapa2.end();it++)
        if(parit[*it])make_edge(*it,sink,1,0);
        else make_edge(source,*it,1,0);

}
int main(){

    ///freopen("test.txt","r",stdin);

    ll sum=0;
    scanf("%d %d",&n,&k);
    source=0;
    sink=n*n+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            sum+=a[i][j];
            num[i][j]=++br;
            parit[br]=(i+j)%2;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%2)continue;

            for(int k1=0;k1<4;k1++){
                int idx=i+dx[k1];
                int idy=j+dy[k1];
                if(idx<1 || idy<1 || idx>n || idy>n)continue;

                /// keeping only best edges that ill use, in order to save memory and time
                mapa.insert({-a[i][j]-a[idx][idy],{num[i][j],num[idx][idy]}});
                if(mapa.size()>7*k){
                    set<pair<int,pii> >::iterator it=mapa.end();
                    it--;
                    mapa.erase(it);
                }
            }
        }
    }

    extract_sufficient_edges();

    johnson();


    int rez=0;
    for(int i=1;i<=k;i++)
        rez+=let_it_flow();

    printf("%lld\n",sum-rez);

return 0;
}
