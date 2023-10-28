/**

    matroids: bipartite matching + mst(non cyclic matroid)

    ICPC Kingdom
    https://codeforces.com/gym/103373/problem/I

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=210;

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

struct edge{
    int u,v,w;
};
vector<edge>e;
vector<int>pm[maxn],rpm[maxn];
struct gse{
    int index;
    bool in_s;
};
vector<int>s;
vector<gse>groundset;
vector<pair<pii,int>>bfe;

int pos[maxn],matched[maxn];
int dfs(int x){

    pos[x]=1;
    for(int i=0;i<pm[x].size();i++){
        int id=pm[x][i]+groundset.size();
        if(matched[id]==-1){
            matched[id]=x;
            matched[x]=id;
            return 1;
        }
        if(pos[matched[id]])continue;
        if(dfs(matched[id])){
            matched[x]=id;
            matched[id]=x;
            return 1;
        }
    }
    return 0;
}
int do_matching(){
    memset(matched,-1,sizeof(matched));
    int ret=0;
    for(int i=0;i<s.size();i++){
        memset(pos,0,sizeof(pos));
        for(int j=0;j<s.size();j++){
            if(pos[s[j]] || matched[s[j]]!=-1)continue;
            if(dfs(s[j])){
                ret++;
                break;
            }
        }
    }
    return ret;
}
vector<int>Y1,y2;
int w,n,m;
int augpos[maxn];
void calc_reachability(){

    queue<int>q;
    memset(augpos,0,sizeof(augpos));
    for(int i=1;i<=w;i++)
        if(matched[i+groundset.size()]==-1)q.push(i+groundset.size());

    while(q.size()){

        int x=q.front();
        q.pop();

        if(x>groundset.size()){
            for(int i=0;i<rpm[x].size();i++){
                int id=rpm[x][i];
                if(augpos[id])continue;
                augpos[id]=1;
                q.push(id);
            }
        }
        else{
            if(matched[x]!=-1){
                augpos[matched[x]]=1;
                q.push(matched[x]);
            }
            else{

            }
        }

    }
}
void prepare_matching(){

    int pom=do_matching();

    for(int i=0;i<s.size();i++){

        int id=s[i];
        int id2=matched[id];
        matched[id]=-1;
        matched[id2]=-1;

        calc_reachability();

        for(int j=0;j<groundset.size();j++){
            if(groundset[j].in_s)continue;
            int ee=0;
            if(augpos[j])ee=1;
            if(ee)
                bfe.pb({ {s[i],j}, e[j].w });

        }

        matched[id]=id2;
        matched[id2]=id;
    }

    Y1.clear();
    calc_reachability();
    for(int j=0;j<groundset.size();j++){
        if(groundset[j].in_s)continue;
        int e=0;
        if(augpos[j])e=1;
        if(e)Y1.pb(j);
    }

}
void prepare_mst(){

    dsu d(n);
    y2.clear();
    for(int i=0;i<s.size();i++){
        d.reset();
        for(int j=0;j<s.size();j++){
            if(j==i)continue;
            d.join(e[s[j]].u,e[s[j]].v);
        }

        for(int j=0;j<groundset.size();j++){
            if(groundset[j].in_s)continue;

            if(d.root(e[j].u)!=d.root(e[j].v)){
                bfe.pb({ {j,s[i]} , -e[ s[i]].w});
            }
        }
    }
    d.reset();
    for(int j=0;j<s.size();j++){
        d.join(e[s[j]].u,e[s[j]].v);
    }
    for(int j=0;j<groundset.size();j++){
        if(groundset[j].in_s)continue;

        if(d.root(e[j].u)!=d.root(e[j].v)){
            y2.pb(j);
        }
    }

}

bool augment(int ct){

    bfe.clear();
    prepare_matching();
    prepare_mst();

    vector<pii>dist(groundset.size(),{1e9,1e9});
    vector<int>p(groundset.size(),-1);

    for(int i=0;i<Y1.size();i++){
        int id=Y1[i];
        dist[id]={-e[id].w,1};
        p[id]=-2;
    }

    for(int i=0;i<groundset.size();i++)
    for(int j=0;j<bfe.size();j++){
        int u=bfe[j].ff.ff;
        int v=bfe[j].ff.ss;
        int w=-bfe[j].ss;

        if(p[u]==-1)continue;

        if(dist[v]>(pii){dist[u].ff+w,dist[u].ss+1}){
            dist[v]={dist[u].ff+w,dist[u].ss+1};
            p[v]=u;
            //printf("%d %d UPDATE\n",v,u);
        }
    }

    int id=-1;
    for(int i=0;i<y2.size();i++){
        if(p[y2[i]]==-1)continue;
        if(id==-1)id=y2[i];
        else{
            if(dist[id]>dist[y2[i]])id=y2[i];
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
    for(int i=0;i<groundset.size();i++){
        if(groundset[i].in_s)s.pb(i);
    }

    return true;
}
void go(){

    int cc=n-1;
    int ct=1;
    while(augment(ct)){
        int rez=0;
        for(int i=0;i<s.size();i++){
            int id=groundset[s[i]].index;
            rez+=e[id].w;
        }
        printf("%d ",rez);
        cc--;
        ct++;
    }

    while(cc--){
        printf("-1 ");
    }
    printf("\n");

}

int a[maxn];
int main(){


    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d",&u,&v);
        w=sqrt(a[u]+a[v]);
        groundset.pb({e.size(),false});
        e.pb({u,v,w});
    }

    scanf("%d",&w);
    for(int i=1;i<=w;i++){
        int x;
        scanf("%d",&x);
        for(int j=1;j<=x;j++){
            int b;
            scanf("%d",&b);
            b--;
            pm[b].pb(i);
            rpm[i+m].pb(b);
        }
    }

    go();

    return 0;
}
