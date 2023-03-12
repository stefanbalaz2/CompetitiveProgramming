/*

    idea: binary search the answer, then we get edges, some have a direction, some need to be directed in some way
    use flow to direct edges such that we have an euler cycle

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,int> pii;
const int maxn=1010;
int source,sink,level[maxn],inf=1e9,deg[maxn],n,m,a[2*maxn],b[2*maxn],l[2*maxn],p[2*maxn],start[maxn],deg2[maxn];
struct edge{
    int a,b,flow,cap;
};
vector<edge>e;
vector<int>v[maxn],v2[maxn],path;
vector<pii>vect[maxn];
map<pii,int>mapa;
int sign(int x){
    if(x>=0)return 1;
    return -1;
}
void reset_flow(){
    e.clear();
    for(int i=source;i<=sink;i++)v[i].clear();
}
void add_edge(int x,int y,int cap){

    v[x].pb(e.size());
    e.pb({x,y,0,cap});

    v[y].pb(e.size());
    e.pb({y,x,cap,cap});
}
int bfs(){

    queue<int>q;
    memset(level,0,sizeof(level));
    level[source]=1;
    q.push(source);

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<v[x].size();i++){
            int id=v[x][i];
            if(e[id].flow>=e[id].cap || level[e[id].b])continue;

            level[e[id].b]=level[x]+1;
            q.push(e[id].b);
        }

    }

    return level[sink];
}
int send_flow(int x,int flow){

    if(x==sink)return inf;

    for(;start[x]<v[x].size();start[x]++){

        int id=v[x][start[x]];

        if(e[id].flow<e[id].cap && level[x]+1==level[e[id].b]){

            int temp_flow=send_flow(e[id].b,min(flow,e[id].cap-e[id].flow));

            if(temp_flow){

                int fl=min(e[id].cap-e[id].flow,temp_flow);

                e[id].flow+=min(fl,flow);
                e[id^1].flow-=min(fl,flow);

                return fl;
            }

        }

    }

    return 0;
}
void flow_it(){

    while(bfs()){
        memset(start,0,sizeof(start));
        while(send_flow(source,inf)){}
    }
}
bool check_flow(){

    for(int i=0;i<v[source].size();i++){
        int id=v[source][i];
        if(e[id].flow<e[id].cap)return false;
    }

    for(int i=0;i<v[sink].size();i++){
        int id=v[sink][i];
        if(e[id].flow>0)return false;
    }

    return true;
}
bool check(int val){

    memset(deg,0,sizeof(deg));
    for(int i=1;i<=n;i++)vect[i].clear();

    for(int i=1;i<=m;i++){
        if(l[i]>val && p[i]>val)return false;
        if(l[i]<=val && p[i]<=val){
            vect[a[i]].pb({b[i],1});
            deg[a[i]]--;
            deg[b[i]]++;
        }
        else{
            if(l[i]<=val){
                vect[a[i]].pb({b[i],0});
                deg[a[i]]--;
                deg[b[i]]++;
            }
            else{
                vect[b[i]].pb({a[i],0});
                deg[a[i]]++;
                deg[b[i]]--;
            }
        }
    }

    reset_flow();
    /// minus desno
    /// plus levo
    for(int i=1;i<=n;i++){
        if(deg[i]%2)return false;

        int pom=deg[i]/2;
        if(pom<0)pom*=-1;

        if(deg[i]<0)add_edge(i,sink,pom);
        else add_edge(source,i,pom);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j].ff;
            if(vect[i][j].ss==0)continue;

            add_edge(id,i,1);
        }
    }

    flow_it();

    return check_flow();
}
void extract(){

    for(int i=1;i<=n;i++){
        for(int j=0;j<vect[i].size();j++){
            if(vect[i][j].ss==1)continue;
            v2[i].pb(vect[i][j].ff);
        }
    }

    for(int i=1;i<=n;i++){

        for(int j=0;j<v[i].size();j++){

            int id=v[i][j];
            if(e[id].b==sink || e[id].b==source)continue;
            if(e[id].cap>e[id].flow)continue;

            v2[i].pb(e[id].b);
        }

    }
}
void euler(int x){

    while(v2[x].size()){

        int id=v2[x].back();
        v2[x].pop_back();

        euler(id);
    }

    path.pb(x);
}
int main(){


    scanf("%d %d",&n,&m);
    source=0;
    sink=n+1;
    for(int i=1;i<=m;i++){
        scanf("%d %d %d %d",&a[i],&b[i],&l[i],&p[i]);
        mapa[{a[i],b[i]}]=i;
        mapa[{b[i],a[i]}]=i;
    }


    int l=0;
    int r=1000;
    int sr,ret=-1;
    while(l<=r){
        sr=(l+r)/2;

        if(check(sr)){
            ret=sr;
            r=sr-1;
        }
        else l=sr+1;
    }

    if(ret==-1){
        printf("NIE\n");
        return 0;
    }

    check(ret);

    extract();

    euler(1);

    printf("%d\n",ret);
    int last=1;
    for(int i=path.size()-2;i>=0;i--){
        printf("%d ",mapa[{last,path[i]}]);
        last=path[i];
    }

	return 0;
}
