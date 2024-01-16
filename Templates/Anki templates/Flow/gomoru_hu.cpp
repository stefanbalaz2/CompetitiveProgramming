/// https://loj.ac/p/2042
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=860;

struct edge{
    int u,v,f,c;
};
vector<edge>e;
vector<int>vect[maxn];
int start[maxn],dist[maxn],n,m;
void add_edge(int u,int v,int w){

    vect[u].pb(e.size());
    e.pb({u,v,0,w});

    vect[v].pb(e.size());
    e.pb({v,u,w,w});
}

int bfs(int x,int y){

    queue<int>q;
    q.push(x);
    for(int i=1;i<=n;i++)dist[i]=0;
    dist[x]=1;

    while(q.size()){
        x=q.front();
        q.pop();
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].f==e[id].c || dist[e[id].v])continue;
            dist[e[id].v]=dist[x]+1;
            q.push(e[id].v);
        }
    }

    return dist[y];
}
int dfs(int x,int sink,int flow){

    if(x==sink)return flow;

    int sum=0;
    for(;start[x]<vect[x].size();start[x]++){

        int id=vect[x][start[x]];

        if(e[id].f<e[id].c && dist[x]+1==dist[e[id].v]){

            int tmp=dfs(e[id].v,sink,min(flow,e[id].c-e[id].f));

            if(tmp){
                e[id].f+=tmp;
                e[id^1].f-=tmp;
                sum+=tmp;
                flow-=tmp;
                if(flow==0)return sum;
            }

        }

    }

    return sum;
}
int get_flow(int x,int y){

    for(int i=0;i<e.size();i+=2){
        e[i].f=0;
        e[i^1].f=e[i^1].c;
    }

    int ret=0;
    while(bfs(x,y)){

        memset(start,0,sizeof(start));
        int pom;
        while(pom=dfs(x,y,1e9))ret+=pom;

    }

    return ret;
}
int rez=0;
vector<pair<pii,int>>ght;
void build(vector<int>a){

    if(a.size()==1)return;

    int pom=get_flow(a[0],a[1]);
    rez+=pom;
    ght.pb({{a[0],a[1]},pom});
    vector<int>t1,t2;
    for(int i=0;i<a.size();i++)
        if(dist[a[i]])t1.pb(a[i]);
        else t2.pb(a[i]);

    build(t1);
    build(t2);
}

int par[maxn];
vector<int>path[maxn];
int root(int x){
    if(par[x]==x)return x;
    return par[x]=root(par[x]);
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }

    vector<int>a;
    for(int i=1;i<=n;i++){
        a.pb(i);
        par[i]=i;
        path[i].pb(i);
    }
    build(a);

    set<int>st;
    for(int i=0;i<ght.size();i++){
        st.insert(ght[i].ss);
    }
    printf("%d\n",st.size());

    return 0;
}
