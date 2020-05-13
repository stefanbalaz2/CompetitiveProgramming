/*

    idea: construct a flow network
    source connected to the positive value nodes with flow equal to it
    negative val nodes connected to sink with abs val of their value
    edge a->b exists if b is reachable from a, a has positive val, b has negative val
    result is: (sum of positive nodes) - (maxflow)

    case to handle: when the result equals 0
    we need to check if there exist a positive node which doesnt have a path to sink
    if it exists then the answer is 0
    else we cant invite anyone

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,ll> pii;
const int maxn=110;
int inf=1e9;
struct edge{
    int a,b,flow,cap;
};
vector<edge>e;
vector<int>v[maxn],vect[maxn];
int a[maxn],pos[maxn],level[maxn],start[maxn],source,sink,n;
void add_edge(int a,int b,int cap){

    vect[a].pb(e.size());
    e.pb({a,b,0,cap});

    vect[b].pb(e.size());
    e.pb({b,a,cap,cap});
}
void dfs(int x,int s){

    if(a[x]<0)add_edge(s,x,inf);

    pos[x]=1;
    for(int i=0;i<v[x].size();i++){
        int id=v[x][i];
        if(pos[id])continue;

        dfs(id,s);
    }

}
int bfs(){


    memset(level,0,sizeof(level));
    level[source]=1;


    queue<int>q;
    q.push(source);

    while(q.size()){


        int x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(level[e[id].b] || e[id].flow>=e[id].cap)continue;

            level[e[id].b]=level[x]+1;
            q.push(e[id].b);
        }
    }

    return level[sink];
}
int send_flow(int x,int fl){

    if(x==sink)return inf;

    for(;start[x]<vect[x].size();start[x]++){
        int id=vect[x][start[x]];

        if(e[id].flow<e[id].cap && level[x]+1==level[e[id].b]){

            int temp_flow=send_flow(e[id].b,min(fl,e[id].cap-e[id].flow));

            if(temp_flow){

                int acflow=min(fl,min(temp_flow,e[id].cap-e[id].flow));
                int ret=min(temp_flow,e[id].cap-e[id].flow);

                e[id].flow+=acflow;
                e[id^1].flow-=acflow;

                return ret;
            }

        }

    }


return 0;
}
int go(){

    int ret=0;

    while(bfs()){

        memset(start,0,sizeof(start));

        while(1){
            int pom=send_flow(source,inf);
            if(pom==0)break;
            ret+=pom;
        }
    }

    return ret;
}
bool check2(int x){

    memset(pos,0,sizeof(pos));
    queue<int>q;

    q.push(x);

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(pos[e[id].b] || e[id].flow>=e[id].cap)continue;

            pos[e[id].b]=1;
            q.push(e[id].b);
        }

    }

    if(pos[sink])return false;
    return true;

}
bool check(){

    for(int i=1;i<=n;i++)
        if(a[i]>=0){
            if(check2(i))return true;
        }

    return false;
}
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    int po=0;
    while(t--){

        po++;
        scanf("%d",&n);

        e.clear();
        for(int i=0;i<=n+1;i++){
            vect[i].clear();
            v[i].clear();
        }

        source=0;
        sink=n+1;
        int sum=0;
        for(int i=1;i<=n;i++){
            int g;
            scanf("%d %d",&a[i],&g);

            if(a[i]>=0){
                add_edge(source,i,a[i]);
                sum+=a[i];
            }
            else add_edge(i,sink,-a[i]);

            for(int j=1;j<=g;j++){
                int p;
                scanf("%d",&p);
                v[i].pb(p);
            }
        }

        for(int i=1;i<=n;i++){
            memset(pos,0,sizeof(pos));
            if(a[i]<0)continue;
            dfs(i,i);
        }

        int rez=sum-go();
        printf("Case #%d: ",po);
        if(rez==0){
            if(check())printf("0\n");
            else printf("Alas, sultan can't invite anyone!\n");
        }
        else printf("%d\n",rez);
    }

	return 0;
}
