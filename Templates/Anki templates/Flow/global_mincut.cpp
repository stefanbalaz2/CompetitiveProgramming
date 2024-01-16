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

int n,m;

int par[maxn];
int root(int x){
    if(par[x]==x)return x;
    return par[x]=root(par[x]);
}

vector<pair<pii,int>>edges;
vector<pii>g[maxn];
int pos[maxn],w[maxn];
int mincut_phase(){

    set<pii>st;
    for(int i=1;i<=n;i++){
        w[i]=0;
        pos[i]=0;
        if(par[i]==i)st.insert({0,i});
    }

    int prv=-1;
    while(st.size()>1){

        int x=(*st.rbegin()).ss;
        prv=x;
        pos[x]=1;
        st.erase(*st.rbegin());
        for(int j=0;j<g[x].size();j++){
            int id=g[x][j].ff;
            int ew=g[x][j].ss;
            if(pos[id])continue;
            st.erase({w[id],id});
            w[id]+=ew;
            st.insert({w[id],id});

        }

    }

    par[prv]=(*st.begin()).ss;

    return (*st.begin()).ff;
}
int get_mincut(){

    for(int i=1;i<=n;i++){
        par[i]=i;
    }

    int ret=2e9;
    for(int i=1;i<n;i++){

        for(int j=1;j<=n;j++){
            g[j].clear();
        }
        for(int j=0;j<edges.size();j++){
            int u=root(edges[j].ff.ff);
            int v=root(edges[j].ff.ss);
            int w=edges[j].ss;
            if(u==v)continue;
            g[u].pb({v,w});
            g[v].pb({u,w});
        }

        ret=min(ret,mincut_phase());
    }

    return ret;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        edges.pb({{u,v},w});
    }

    int mc=get_mincut();


    return 0;
}
