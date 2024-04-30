#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxm=1e5+10;
const int maxn=2e3+10;

int n,m;

namespace gomoru{


    mt19937 gen(10);
    struct edge{
        int u,v,f,c;
    };
    vector<edge>e;
    vector<int>vect[maxn];
    int start[maxn],dist[maxn];
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
    int cnt=0;
    void build(vector<int>a){

        ///shuffle(a.begin(),a.end(),gen);

        if(a.size()==1)return;

        int pom=get_flow(a[0],a[1]);
        ght.pb({{a[0],a[1]},pom});
        vector<int>t1,t2;
        for(int i=0;i<a.size();i++)
            if(dist[a[i]])t1.pb(a[i]);
            else t2.pb(a[i]);

        printf("%d %d %d CNT\n",cnt++,t1.size(),t2.size());
        build(t1);
        build(t2);
    }

    vector<pair<pii,int>> get_gomory(){
        ght.clear();
        vector<int>a;
        for(int i=1;i<=n;i++)a.pb(i);
        build(a);
        return ght;
    }

}

struct dsu{

    int n;
    int cc;
    vector<int>p,sz;

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

vector<pii>edges,gtree[maxn];
int pos[maxn];
void mrg_comps(int x,int prv,int rt,dsu &d){
    d.join(rt,x);
    pos[x]=1;
    for(int i=0;i<gtree[x].size();i++){
        int id=gtree[x][i].ff;
        int w=gtree[x][i].ss;
        if(id==prv || w<=2)continue;

        mrg_comps(id,x,rt,d);
    }
}

int hh[maxn];
vector<int>vect[maxn];
int get_nxt(int eid,int x){
    if(edges[eid].ff==x)return edges[eid].ss;
    else return edges[eid].ff;
}
void dfs(int x,int h,vector<int>&szs){

    hh[x]=h;
    for(int i=0;i<vect[x].size();i++){
        int eid=vect[x][i];
        if(pos[eid])continue;
        int nxt=get_nxt(eid,x);

        pos[eid]=1;
        if(hh[nxt]){
            szs.pb(hh[x]-hh[nxt]+1);
            continue;
        }
        dfs(nxt,h+1,szs);
    }

}

vector<int>pvect[maxn];
namespace brid{
    int disc[maxn],minv[maxn],ctm;

    void dfs(int x,int prv,int &ret){

        disc[x]=++ctm;
        minv[x]=disc[x];

        for(int i=0;i<pvect[x].size();i++){
            int eid=pvect[x][i];
            int nxt=get_nxt(eid,x);
            if(eid==prv)continue;

            if(disc[nxt]){
                minv[x]=min(minv[x],disc[nxt]);
            }
            else{
                dfs(nxt,eid,ret);
                minv[x]=min(minv[x],minv[nxt]);
                if(disc[x]<minv[nxt])ret++;
            }

        }

    }
    int get_real_bridges(){
        int ret=0;
        dfs(1,-1,ret);
        return ret;
    }
}

int main(){

    freopen("finals/ants.13.in","r",stdin);
    ///freopen("test.txt","w",stdout);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        gomoru::add_edge(u,v,1);
        gomoru::add_edge(v,u,1);
        edges.pb({u,v});

        pvect[u].pb(edges.size()-1);
        pvect[v].pb(edges.size()-1);
    }
    ///printf("ucitao\n");
    vector<pair<pii,int>>tree=gomoru::get_gomory();
    ll bridges=0;
    for(int i=0;i<tree.size();i++){
        gtree[tree[i].ff.ff].pb({tree[i].ff.ss,tree[i].ss});
        gtree[tree[i].ff.ss].pb({tree[i].ff.ff,tree[i].ss});

        ///printf("%d %d | %d\n",tree[i].ff.ff,tree[i].ff.ss,tree[i].ss);
        if(tree[i].ss==1)bridges++;
    }

    int rbridges=brid::get_real_bridges();
    bridges=rbridges;
    ///printf("%d %d BRIDGES\n",bridges,rbridges);

    dsu d(n);
    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        mrg_comps(i,0,i,d);
    }

    vector<pii>pom;
    for(int i=0;i<edges.size();i++){
        int u=edges[i].ff;
        int v=edges[i].ss;
        if(d.root(u)==d.root(v))continue;
        pom.pb({d.root(u),d.root(v)});
    }
    edges=pom;
    for(int i=0;i<edges.size();i++){
        int u=edges[i].ff;
        int v=edges[i].ss;
        vect[u].pb(i);
        vect[v].pb(i);
    }

    ll nobridge=m-bridges;
    ll rez=nobridge*bridges+(bridges*(bridges-1))/2;

    vector<int>cyc_sz;
    memset(pos,0,sizeof(pos));
    dfs(d.root(1),1,cyc_sz);

    for(int i=0;i<cyc_sz.size();i++){
        ll sz=cyc_sz[i];
        rez+=(sz*(sz-1))/2;
        ///printf("%lld SZ\n",sz);
    }

    freopen("finals/ants.13.out","r",stdin);
    ll rez_actual;
    scanf("%lld",&rez_actual);

    printf("%lld %lld\n",rez,rez_actual);

    return 0;
}
