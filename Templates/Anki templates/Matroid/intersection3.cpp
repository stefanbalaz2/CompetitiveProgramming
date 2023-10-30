/**

    matroid intersection: mst + colorful(incremental to find max MEX mst)
    problem: https://qoj.ac/contest/1221/problem/6402

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=1e3+10;

struct dsu{

    int n;
    int cc;
    vector<int>p,sz;


    dsu(){
    }

    dsu(int n){
        this->n=n;
        this->cc=n;
        p.resize(n+1);
        sz.resize(n+1);
        for(int i=1;i<=n;i++){
            p[i]=i;
            sz[i]=1;
        }
    }

    void reset(){
        for(int i=1;i<=n;i++){
            p[i]=i;
            sz[i]=1;
        }
        cc=n;
    }
    int root(int x){
        if(p[x]==x)return x;
        return p[x]=root(p[x]);
    }
    bool join(int u,int v){
        u=root(u);
        v=root(v);
        if(u==v)return false;
        if(sz[u]>sz[v])swap(u,v);
        p[u]=v;
        sz[v]+=sz[u];
        cc--;
        return true;
    }

};

struct edge{
    int u,v,w;
    bool operator <(edge &b){
        return w<b.w;
    }
};
int n,m;
vector<edge>e;
struct gse{
    int index;
    bool in_s;
};
vector<gse>groundset;
vector<int>s;
vector<int>vect[maxn];
dsu d;
int color[maxn];

void prepare_colorful(){
    memset(color,0,sizeof(color));
    for(int i=0;i<s.size();i++)
        color[e[s[i]].w]++;
}
bool oracle_color_swap(int x,int y){
    color[e[x].w]--;
    bool ret=false;
    if(color[e[y].w]==0)ret=true;
    color[e[x].w]++;
    return ret;
}
bool oracle_color_add(int x){
    return color[e[x].w]^1;
}


int tmm=0;
int start[maxn],en[maxn];
void dfs(int x,int prv){
    start[x]=++tmm;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        dfs(id,x);
    }
    en[x]=tmm;
}
void prepare_mst(){

    dsu pom(n);
    d=pom;

    for(int i=1;i<=n;i++)vect[i].clear();
    for(int i=0;i<s.size();i++){
        int id=s[i];
        vect[e[id].u].pb(e[id].v);
        vect[e[id].v].pb(e[id].u);

        d.join(e[id].u,e[id].v);
    }

    tmm=0;
    memset(start,0,sizeof(start));
    memset(en,0,sizeof(en));
    for(int i=1;i<=n;i++){
        if(start[i])continue;
        dfs(i,0);
    }
}
bool oracle_mst_swap(int x,int y){

    int u1,u2,v1,v2;
    u1=e[x].u;
    v1=e[x].v;
    u2=e[y].u;
    v2=e[y].v;

    if(d.root(u2)!=d.root(v2))return true;

    int pom1=(start[u1]<=start[u2] && start[u2]<=en[u1])+(start[u1]<=start[v2] && start[v2]<=en[u1]);
    int pom2=(start[v1]<=start[u2] && start[u2]<=en[v1])+(start[v1]<=start[v2] && start[v2]<=en[v1]);

    pom1=min(pom1,pom2);

    if(pom1==1)return true;
    return false;
}
bool oracle_mst_add(int x){
    int u2,v2;
    u2=e[x].u;
    v2=e[x].v;
    if(d.root(u2)!=d.root(v2))return true;
    return false;
}

vector<int>Y1,Y2;
int endpos[maxn];
bool augment(){

    prepare_mst();
    prepare_colorful();

    Y1.clear();
    Y2.clear();
    for(int i=0;i<groundset.size();i++){
        if(groundset[i].in_s)continue;
        if(oracle_mst_add(i))Y1.pb(i);
        if(oracle_color_add(i))Y2.pb(i);
    }

    queue<int>q;
    vector<int>p(groundset.size(),-1);
    memset(endpos,0,sizeof(endpos));
    for(int i=0;i<Y2.size();i++){
        endpos[Y2[i]]=1;
    }
    int break_condition=0;
    for(int i=0;i<Y1.size();i++){
        int id=Y1[i];
        if(endpos[id])break_condition=1;
        q.push(id);
        p[id]=-2;
    }

    while(q.size()){
        int x=q.front();
        q.pop();

        if(break_condition)break;

        if(groundset[x].in_s){

            /// mst

            for(int i=0;i<groundset.size();i++){
                if(groundset[i].in_s)continue;
                if(p[i]!=-1)continue;
                if(!oracle_mst_swap(x,i))continue;

                q.push(i);
                p[i]=x;
                if(endpos[i])break_condition=1;
                if(break_condition)break;
            }

        }
        else{

            for(int i=0;i<groundset.size();i++){
                if(!groundset[i].in_s)continue;
                if(p[i]!=-1)continue;
                if(!oracle_color_swap(i,x))continue;

                q.push(i);
                p[i]=x;
                if(endpos[i])break_condition=1;
                if(break_condition)break;
            }
        }
    }

    int id=-1;
    for(int i=0;i<Y2.size();i++){
        if(p[Y2[i]]!=-1){
            id=Y2[i];
            break;
        }
    }
    if(id==-1)return false;

    vector<int>path;
    while(id!=-2){
        path.pb(id);
        id=p[id];
    }


    for(int i=0;i<path.size();i++)
        groundset[path[i]].in_s^=1;

    s.clear();
    for(int i=0;i<groundset.size();i++)
        if(groundset[i].in_s)s.pb(i);

    return true;
}

int main(){


    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        e.pb({u,v,w});
    }
    sort(e.begin(),e.end());

    int r=0;
    int rez=0;
    while(r<e.size()){
        int w=e[r].w;
        if(rez!=w)break;
        while(r<e.size() && e[r].w==w){
            groundset.pb({r,false});
            r++;
        }
        if(!augment())break;
        rez++;
    }

    printf("%d\n",rez);

    return 0;
}
