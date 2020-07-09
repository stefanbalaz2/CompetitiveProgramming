/*

    idea: lambda optimisation

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,int> pii;
const int maxn=2e5+10;
int cc,n,m,w,k,sz[maxn],p[maxn],niz[maxn*3],special[maxn];
struct edge{
    int u,v,cost,spec;
}edges[maxn*3];
bool srt(int x,int y){
    return (edges[x].cost<edges[y].cost)||((edges[x].cost==edges[y].cost) && (edges[x].spec>edges[y].spec));
}
void reset_dsu(){

    cc=n;
    for(int i=1;i<=n;i++){
        p[i]=i;
        sz[i]=1;
    }
}
int root(int x){
    if(p[x]==x)return x;
    else return p[x]=root(p[x]);
}
int join(int x,int y){

    x=root(x);
    y=root(y);

    if(x==y)return 0;

    if(sz[x]<sz[y])swap(x,y);

    sz[x]+=sz[y];
    p[y]=x;
    cc--;

    return 1;
}
bool case1(){

    reset_dsu();

    for(int i=1;i<=m;i++){
        int id=niz[i];
        join(edges[id].u,edges[id].v);
    }

    if(cc>1)return true;

    return false;
}
bool case2(){

    reset_dsu();

    for(int i=1;i<=m;i++){
        int id=niz[i];
        if(edges[id].spec)continue;
        join(edges[id].u,edges[id].v);
    }

    int ret=0;
    for(int i=1;i<=m;i++){
        int id=niz[i];
        if(!edges[id].spec)continue;
        ret+=join(edges[id].u,edges[id].v);
    }

    if(ret>w)return true;

    return false;
}
bool case3(){

    reset_dsu();

    int ret=0;
    for(int i=1;i<=m;i++){
        int id=niz[i];
        if(!edges[id].spec)continue;
        ret+=join(edges[id].u,edges[id].v);
    }

    for(int i=1;i<=m;i++){
        int id=niz[i];
        if(edges[id].spec)continue;
        join(edges[id].u,edges[id].v);
    }

    if(ret<w)return true;

    return false;
}
void add_weight(int x){
    for(int i=1;i<=m;i++)
        if(edges[i].spec)edges[i].cost+=x;
}
pii go(){

    reset_dsu();
    sort(niz+1,niz+m+1,srt);

    pii ret={0,0};
    for(int i=1;i<=m;i++){
        int id=niz[i];

        int is=join(edges[id].u,edges[id].v);

        if(is){
            ret.ff+=(ll)edges[id].cost;
            if(edges[id].spec)ret.ss++;
        }
    }

    return ret;
}
int main(){

    ///freopen("hikingtrails-1029.in","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d %d %d %d",&n,&m,&k,&w);
    for(int i=1;i<=k;i++){
        int pom;
        scanf("%d",&pom);
        special[pom]=1;
    }

    for(int i=1;i<=m;i++){
        int u,v,c;
        scanf("%d %d %d",&u,&v,&c);
        bool is=0;
        if((special[u]^special[v]))is=1;
        edges[i]={u,v,c,is};
        niz[i]=i;
    }

    if(case1() || case2() || case3()){
        printf("-1\n");
        return 0;
    }

    int l=-200000;
    int r=2e5;
    int sr,rez=-123;

    while(l<=r){
        sr=(l+r)/2;

        add_weight(sr);

        pii pom=go();

        if(pom.ss>=w){
            l=sr+1;
            rez=sr;
        }
        else r=sr-1;

        add_weight(-sr);
    }

    add_weight(rez);
    pii pom=go();

    printf("%lld\n",pom.ff-(ll)w*rez);

	return 0;
}
