/**

    matroids: edge delete connectivity + edge delete connectivity

    weighted matroid intersection
    problem: https://naipc18.kattis.com/problems/rainbowgraph

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=110;
int n,m;

struct edge{
    int u,v,w;
    bool in1,in2;
};
vector<edge>e;
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

struct gse{
    int index;
    bool in_s;
};
vector<gse>groundset;
vector<int>s;
vector<pair<pii,int>>ge;
vector<int>Y1,y2;
void prepare_g1(){

    Y1.clear();
    dsu pomdsu(n);
    ge.clear();
    for(int i=0;i<groundset.size();i++){
        if(groundset[i].in_s)continue;

        pomdsu.reset();
        for(int j=0;j<groundset.size();j++){
            if(groundset[j].in_s || i==j)continue;
            int id=groundset[j].index;
            if(e[id].in1)pomdsu.join(e[id].u,e[id].v);
        }
        if(pomdsu.cc==1)Y1.pb(i);

        for(int j=0;j<s.size();j++){
            int id=s[j];
            int eid=groundset[id].index;
            int u=e[eid].u;
            int v=e[eid].v;
            bool flag=e[eid].in1;
            if(pomdsu.cc==1 || (pomdsu.cc==2 && flag && pomdsu.root(u)!=pomdsu.root(v)) ){
                ge.pb({{id,i},e[groundset[i].index].w});
            }
        }

    }

}
void prepare_g2(){

    y2.clear();
    dsu pomdsu(n);
    for(int i=0;i<groundset.size();i++){
        if(groundset[i].in_s)continue;

        pomdsu.reset();
        for(int j=0;j<groundset.size();j++){
            if(groundset[j].in_s || i==j)continue;
            int id=groundset[j].index;
            if(e[id].in2)pomdsu.join(e[id].u,e[id].v);
        }
        if(pomdsu.cc==1)y2.pb(i);

        for(int j=0;j<s.size();j++){
            int id=s[j];
            int eid=groundset[id].index;
            int u=e[eid].u;
            int v=e[eid].v;
            bool flag=e[eid].in2;
            if(pomdsu.cc==1 || (pomdsu.cc==2 && flag && pomdsu.root(u)!=pomdsu.root(v)) ){
                ge.pb({{i,id},-e[groundset[id].index].w});
            }
        }

    }

}
bool augment(int &csum){

    prepare_g1();
    prepare_g2();

    vector<pii>dist(groundset.size(),{1e9,1e9});
    vector<int>par(groundset.size(),-1);

    for(int i=0;i<Y1.size();i++){
        int id=Y1[i];
        dist[id]={-e[groundset[id].index].w,1};
        par[id]=-2;
    }

    for(int i=0;i<groundset.size();i++){
        for(int j=0;j<ge.size();j++){

            int u=ge[j].ff.ff;
            int v=ge[j].ff.ss;
            int w=-ge[j].ss;

            if(par[u]==-1)continue;

            if(dist[v]>(pii){dist[u].ff+w,dist[u].ss+1}){
                dist[v].ff=dist[u].ff+w;
                dist[v].ss=dist[u].ss+1;
                par[v]=u;
            }
        }
    }

    int id=-1;
    for(int i=0;i<y2.size();i++){
        if(par[y2[i]]==-1)continue;
        if(id==-1 || dist[id]>dist[y2[i]])id=y2[i];
    }
    if(id==-1)return false;

    while(id!=-2){
        groundset[id].in_s^=1;
        id=par[id];
    }

    s.clear();
    csum=0;
    for(int i=0;i<groundset.size();i++){
        if(!groundset[i].in_s)continue;
        s.pb(i);
        csum+=e[groundset[i].index].w;
    }

    return true;
}

void solve(int csum){

    vector<int>rez(m+1,-1);
    rez[m]=csum;
    int sum=csum;
    int id=m;
    while(augment(csum)){
        id--;
        rez[id]=sum-csum;
    }

    for(int i=1;i<=m;i++){
        printf("%d\n",rez[i]);
    }

}
int main(){


    ///freopen("secret/rainbow-1000.in","r",stdin);

    scanf("%d %d",&n,&m);

    dsu d1(n);
    dsu d2(n);
    int csum=0;
    for(int i=1;i<=m;i++){

        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        char c;
        cin>>c;

        bool c1,c2;
        c1=true;
        c2=true;
        if(c=='R')c1=false;
        if(c=='B')c2=false;

        if(c1)d1.join(u,v);
        if(c2)d2.join(u,v);

        e.pb({u,v,w,c1,c2});
        groundset.pb({(int)e.size()-1,false});
        csum+=w;
    }

    if(d1.cc!=1 || d2.cc!=1){
        for(int i=1;i<=m;i++)printf("-1\n");
        return 0;
    }
    solve(csum);


    return 0;
}
