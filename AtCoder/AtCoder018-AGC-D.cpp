/*

    idea=https://img.atcoder.jp/agc018/editorial.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,ll> pii;
const int maxn=1e5+10;
int sz[maxn],center,n,maxx;
ll dist[maxn],rez;
vector<pii>vect[maxn];
void prek(int x,int prv){

    sz[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        if(id==prv)continue;

        prek(id,x);
        sz[x]+=sz[id];
    }
}

void gc(int x,int prv){

    int e=0;
    e=max(e,n-sz[x]);
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        if(id==prv)continue;

        e=max(e,sz[id]);
    }
    if(e<maxx){
        center=x;
        maxx=e;
    }

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        if(id==prv)continue;

        gc(id,x);
    }

}
void go(int x,int prv,ll pd){

    dist[x]=dist[prv]+pd;
    rez+=dist[x]*2;

    ///printf("%d %lld AA\n",x,dist[x]);

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        ll w=vect[x][i].ss;
        if(prv==id)continue;

        go(id,x,w);
    }

}
int main(){

    scanf("%d",&n);
    maxx=1e9;
    for(int i=1;i<n;i++){
        int u,v;
        ll w;
        scanf("%d %d %lld",&u,&v,&w);
        vect[u].pb({v,w});
        vect[v].pb({u,w});
    }

    prek(1,0);
    gc(1,0);

    go(center,0,0);
    prek(center,0);

    if(n==1){
        printf("0\n");
        return 0;
    }

    ///printf("%d\n",center);

    int x=center;

    ll minn=1e9;
    if(maxx>n-1-maxx){
        int szz=0;
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i].ff;

            ///printf("%d %lld dasaa\n",sz[id],vect[x][i].ss);

            if(sz[id]>szz){
                szz=sz[id];
                minn=vect[x][i].ss;
            }
        }
    }
    else{
        for(int i=0;i<vect[x].size();i++){
            minn=min(minn,vect[x][i].ss);
        }
    }

    printf("%lld\n",rez-minn);

return 0;
}
