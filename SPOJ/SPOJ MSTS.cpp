/*
     https://github.com/quangloc99/CompetitiveProgramming/blob/master/SPOJ/MSTS.cpp
*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair< ll,ll> pii;
const ll maxn=110;
ll mod=31011,mod1=3,mod2=31011/3;
ll pos[maxn],lap[maxn][maxn],n,p[maxn],sz[maxn],m,rez1=1,rez2=1;
map<ll,vector<pii> >mapa;
vector<ll>edges[maxn];
void regulate(ll &x,ll m){
    x%=m;
    if(x<0)x+=m;
}
ll mul(ll x,ll y,ll m){
    regulate(x,m);
    regulate(y,m);
    ll ret=x*y;
    regulate(ret,m);
    return ret;
}
ll step(ll x,ll pw,ll m){
    ll ret=1;
    for(ll i=0;i<=20;i++){
        if(pw&(1<<i))ret=mul(ret,x,m);
        x=mul(x,x,m);
    }
return ret;
}
ll div(ll x,ll y,ll m){
    regulate(x,m);
    regulate(y,m);
    ll ret=x*step(y,m-2,m);
    regulate(ret,m);
    return ret;
}
ll add(ll x,ll y,ll m){
    ll ret=x+y;
    regulate(ret,m);
    return ret;
}
void scale(vector<pii> &vect){

    map<ll,ll>mapa;
    for(ll i=0;i<vect.size();i++)mapa[vect[i].ff]=0,mapa[vect[i].ss]=0;

    ll br=0;
    for(map<ll,ll>::iterator it=mapa.begin();it!=mapa.end();it++)it->ss=++br;

    for(ll i=0;i<vect.size();i++)vect[i].ff=mapa[vect[i].ff],vect[i].ss=mapa[vect[i].ss];
}
void color(ll x,vector<ll> &vect){

    pos[x]=1;
    vect.pb(x);
    for(ll i=0;i<edges[x].size();i++){
        ll id=edges[x][i];
        if(pos[id])continue;
        color(id,vect);
    }
}
ll swapRow(int r1,int r2,ll m,int n){
    if(r1==r2)return 1;
    for(int i=1;i<=n;i++)swap(lap[r1][i],lap[r2][i]);
    return m-1;
}
ll mulRow(int r1,ll sc,ll m,int n){
    regulate(sc,m);
    for(int i=1;i<=n;i++)lap[r1][i]=mul(lap[r1][i],sc,m);
    return sc;
}
ll addRowScalar(int r1,int r2,ll sc,ll m,int n){

    regulate(sc,m);
    for(int i=1;i<=n;i++){
        lap[r1][i]=add(lap[r1][i], mul(sc,lap[r2][i],m) ,m);
    }

return 1;
}
ll determinant(ll n,ll m){

    ///correct matrix
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=n;j++)
            regulate(lap[i][j],m);


    ll det=1;
    ll fac=1;
    for(ll i=1;i<=n;i++){
      int id=0;
      for (int j=i;j<=n;j++)
        if(lap[j][i]!=0){
          id=j;
          break;
        }

      if(id==0)return 0;
      det=mul(det,lap[id][i],m);
      if(id!=i)det=mul(det,-1,m);

      for(int j=1;j<=n;j++)swap(lap[id][j],lap[i][j]);

      for(int j=i+1;j<=n;j++){
        if(lap[j][i]==0)continue;

        ll pom=div(lap[j][i],lap[i][i],m);

        for(int k=1;k<=n;k++)
            lap[j][k]=add(lap[j][k],mul(lap[i][k],-pom,m),m);

      }
    }

return det;
}
ll evaluate(vector<pii> &vect,ll m){/// vect = edges of the graph, function counts number of spanning trees

    memset(lap,0,sizeof(lap));
    ll maxx=0;
    for(ll i=0;i<vect.size();i++){
        ll id=vect[i].ff;
        ll id2=vect[i].ss;

        maxx=max(maxx,id);
        maxx=max(maxx,id2);

        lap[id][id2]--;
        lap[id2][id]--;

        lap[id][id]++;
        lap[id2][id2]++;
    }

    for(ll i=1;i<=maxx;i++)
        for(ll j=1;j<=maxx;j++)
            lap[i][j]=div(lap[i][j],2,m);

    maxx--;
    ll pom=determinant(maxx,m);

    return pom;
}
ll root(ll x){
    if(x==p[x])return x;
    return p[x]=root(p[x]);
}
void join(ll x,ll y){
    if(root(x)==root(y))return;
    p[root(x)]=root(y);
}
ll graph_mst_count(vector<pii> vect,ll m){


    /// corrent the edges
    set<ll>nodes;
    for(ll i=1;i<=n;i++)edges[i].clear();

    for(ll i=0;i<vect.size();i++){
        vect[i].ff=root(vect[i].ff);
        vect[i].ss=root(vect[i].ss);

        if(vect[i].ff==vect[i].ss)continue;

        nodes.insert(vect[i].ff);
        nodes.insert(vect[i].ss);
        edges[vect[i].ff].pb(vect[i].ss);
        edges[vect[i].ss].pb(vect[i].ff);
    }

    /// find components, scale them, and evaluate them
    memset(pos,0,sizeof(pos));
    ll ret=1;
    for(set<ll>::iterator it=nodes.begin();it!=nodes.end();it++){
        if(pos[*it])continue;
        vector<ll>vnodes;
        color(*it,vnodes);

        vector<pii>eval;
        for(ll j=0;j<vnodes.size();j++){
            ll id=vnodes[j];
            for(ll k=0;k<edges[id].size();k++)
                eval.pb((pii){id,edges[id][k]});
        }

        scale(eval);
        ret=mul(ret,evaluate(eval,m),m);

    }

    /// join graph
    for(ll i=0;i<vect.size();i++)
        join(vect[i].ff,vect[i].ss);

    return ret;
}
void reset_dsu(){

    for(ll i=1;i<=n;i++){
        p[i]=i;
        sz[i]=1;
    }

}
ll get_result(ll x,ll y){

    for(ll i=0;i<mod;i++){
        if(i%mod1==x && i%mod2==y)return i;
    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%lld %lld",&n,&m);
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        scanf("%lld %lld %lld",&u,&v,&w);
        mapa[w].pb({u,v});
    }

    reset_dsu();
    for(map<ll,vector<pii> >::iterator it=mapa.begin();it!=mapa.end();it++)
        rez1=mul(rez1,graph_mst_count(it->ss,mod1),mod1);


    for(ll i=1;i<n;i++)if (root(i) != root(i + 1)){
        printf("0\n");
        return 0;
    }

    reset_dsu();
    for(map<ll,vector<pii> >::iterator it=mapa.begin();it!=mapa.end();it++)
        rez2=mul(rez2,graph_mst_count(it->ss,mod2),mod2);


    printf("%lld\n",get_result(rez1,rez2));

    return 0;
}
