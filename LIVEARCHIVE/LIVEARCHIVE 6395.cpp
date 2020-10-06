/*

    idea:   different distance paths are independend
            solve for same length paths
            maxflow problem, sink=1, adda source and connect it to
            all the starting points, every edge capacity 1


*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef map<int,vector<int> >::iterator mit;
int inf=1e9;
const int maxn=25010;
struct edge{
    int a,b,flow;
};
vector<edge>e;
vector<int>vf[maxn];
vector<pii>vect[maxn];
int n,a[maxn],c,m,dist[maxn],level[maxn],sink,source,start[maxn];
map<int,vector<int> >mapa;
void prek(){

    fill(dist,dist+n+1,inf);
    dist[1]=0;
    set<pii>st;
    st.insert({0,1});

    while(st.size()){

        int x=(*st.begin()).ss;
        st.erase(st.begin());

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i].ff;
            int w=vect[x][i].ss;
            if(dist[id]<dist[x]+w)continue;

            st.erase({dist[id],id});
            dist[id]=dist[x]+w;
            st.insert({dist[id],id});
        }
    }
}
void group_them(){
    for(int i=1;i<=c;i++)
        mapa[dist[a[i]]].pb(a[i]);
}
void add_edge(int x,int y){
    vf[x].pb(e.size());
    e.pb({x,y,0});

    vf[y].pb(e.size());
    e.pb({y,x,1});
}
int bfs(){

    memset(level,0,sizeof(level));
    level[source]=1;
    queue<int>q;
    q.push(source);

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<vf[x].size();i++){
            int id=vf[x][i];
            if(level[e[id].b])continue;
            if(e[id].flow)continue;

            level[e[id].b]=level[x]+1;
            q.push(e[id].b);
        }

    }

    return level[sink];
}
int send_flow(int x,int flow){

    if(x==sink)return flow;

    for(;start[x]<vf[x].size();start[x]++){

        int id=vf[x][start[x]];

        if(e[id].flow==0 && level[e[id].b]==level[x]+1){

            int temp_flow=send_flow(e[id].b,min(1,flow));

            if(temp_flow){

                e[id].flow^=1;
                e[id^1].flow^=1;

                return 1;
            }

        }

    }

    return 0;
}
int get_flow(){

    int ret=0;

    while(bfs()){

        memset(start,0,sizeof(start));
        while(1){
            int pom=send_flow(source,1);
            if(pom==0)break;
            ret+=pom;
        }
    }

    return ret;
}
int do_them(vector<int> &v){

    e.clear();
    for(int i=source;i<=n;i++)vf[i].clear();

    for(int i=1;i<=n;i++){
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j].ff;
            int w=vect[i][j].ss;

            if(dist[id]==dist[i]+w){
                add_edge(id,i);
            }
        }
    }
    for(int i=0;i<v.size();i++)add_edge(source,v[i]);

    return get_flow();
}
int main(){

    ///freopen("test.txt","r",stdin);
    while(scanf("%d %d %d",&n,&m,&c)==3){
        source=0;
        sink=1;
        for(int i=1;i<=n;i++)vect[i].clear();
        mapa.clear();
        for(int i=1;i<=m;i++){
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            vect[u].pb({v,w});
            vect[v].pb({u,w});
        }
        for(int i=1;i<=c;i++)scanf("%d",&a[i]);

        prek();
        group_them();

        int rez=0;
        for(mit it=mapa.begin();it!=mapa.end();it++)
            rez+=do_them(it->ss);

        printf("%d\n",rez);
    }

    return 0;
}
