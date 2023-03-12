/*

    idea: https://codeforces.com/blog/entry/61356

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef multiset<int>::iterator sit;
const int maxn=5e5+10;
int n,k,m,p[maxn],color[maxn],level[maxn],dp[maxn][20],clr,pos[maxn],e,sz[maxn];
vector<pii>vect[maxn];
vector<int>ubaci[maxn],izbaci[maxn];
multiset<int>st[maxn];
ll rez;
void paint(int x,int prv,int lvl){

    level[x]=lvl;
    dp[x][0]=prv;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        if(id==prv)continue;
        paint(id,x,lvl+1);
    }
}
void prek(){
    int h=log2(n);
    for(int i=1;i<=h;i++)
        for(int j=1;j<=n;j++)
        dp[j][i]=dp[dp[j][i-1]][i-1];
}
int lca(int x,int y){

    int h=log2(n);
    if(level[x]<level[y])swap(x,y);

    for(int i=h;i>=0;i--){
        if(level[dp[x][i]]<level[y])continue;
        x=dp[x][i];
    }

    if(x==y)return x;

    for(int i=h;i>=0;i--){
        if(dp[x][i]==dp[y][i])continue;
        x=dp[x][i];
        y=dp[y][i];
    }

    return dp[x][0];
}
void go(int x,int prv,int imp){

    pos[x]=1;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        int imp2=vect[x][i].ss;
        if(id==prv)continue;

        go(id,x,imp2);

        if(st[x].size()<st[id].size())swap(st[x],st[id]);

        for(sit it=st[id].begin();it!=st[id].end();it++)
            st[x].insert(*it);

        st[id].clear();
    }

    for(int i=0;i<ubaci[x].size();i++){
        int id=ubaci[x][i];
        st[x].erase(st[x].find(id));
    }
    for(int i=0;i<izbaci[x].size();i++){
        int id=izbaci[x][i];
        st[x].insert(id);
    }
    ubaci[x].clear();
    izbaci[x].clear();

    if(prv!=0){

        if(imp==0){}
        else{
            if(st[x].size()==0)e=1;
            else rez+=(ll)(*st[x].begin());
        }
    }

}
void reset_dsu(){
    for(int i=1;i<=n;i++){
        sz[i]=1;
        p[i]=i;
    }
}
int root(int x){
    if(p[x]==x)return x;
    else return p[x]=root(p[x]);
}
void join(int x,int y){

    x=root(x);
    y=root(y);

    if(x==y)return;

    if(sz[x]<sz[y])swap(x,y);

    sz[x]+=sz[y];
    p[y]=x;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d %d",&n,&k,&m);

    reset_dsu();
    for(int i=1;i<=k;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb({v,1});
        vect[v].pb({u,1});
        join(u,v);
    }

    vector<pair<pii,int> >cand;
    for(int i=1;i<=m;i++){
        int u,v;
        int w;
        scanf("%d %d %d",&u,&v,&w);

        if(root(u)==root(v)){
            cand.pb({{u,v},w});
        }
        else{
            join(u,v);
            vect[u].pb({v,0});
            vect[v].pb({u,0});
        }
    }

    paint(1,0,1);
    prek();

    for(int i=0;i<cand.size();i++){
        int u=cand[i].ff.ff;
        int v=cand[i].ff.ss;
        int w=cand[i].ss;

        int lc=lca(u,v);

        if(level[u]>level[v])swap(u,v);

        if(u==lc){
            ubaci[u].pb(w);
            izbaci[v].pb(w);
        }
        else{
            ubaci[lc].pb(w);
            izbaci[u].pb(w);
            ubaci[lc].pb(w);
            izbaci[v].pb(w);
        }
    }

    go(1,0,0);

    if(!e)printf("%lld\n",rez);
    else printf("-1\n");

    return 0;
}
