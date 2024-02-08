#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxm=10010;
const int maxn=5010;

mt19937_64 gen(10);
ll rval[maxm];
vector<pii>vect[maxn];
int n,m;

struct edge{
    int u,v;
    ll w;
};
vector<edge>edges;
int h[maxn],pos[maxn],p[maxn];
vector<vector<int>>cycles;
void go(int x,int prv,int peid,int hh){

    h[x]=hh;
    pos[x]=1;
    p[x]=peid;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        if(pos[id]){
            if(h[id]>h[x] || id==prv)continue;

            vector<int>cyc;
            cyc.pb(vect[x][i].ss);
            int curr=x;
            while(curr!=id){
                cyc.pb(p[curr]);
                ///printf("%d AA\n",curr);
                if(edges[p[curr]].u==curr)curr=edges[p[curr]].v;
                else curr=edges[p[curr]].u;
            }
            cycles.pb(cyc);
        }
        else{
            go(id,x,vect[x][i].ss,hh+1);
        }
    }

}
ll hval[maxm];
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        vect[u].pb({v,i-1});
        vect[v].pb({u,i-1});
        edges.pb({u,v,w});
    }

    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        go(i,0,-1,1);
    }
    if(cycles.size()==0){
        printf("0\n");
        return 0;
    }
    for(int i=0;i<cycles.size();i++)
        rval[i]=gen();

    vector<ll>cvals;
    ll cycle_gcd=0;
    for(int i=0;i<cycles.size();i++){
        vector<int>&a=cycles[i];
        ll pom=0;
        for(auto x:a){
            hval[x]^=rval[i];
            pom+=edges[x].w;
        }
        cvals.pb(pom);
        cycle_gcd=__gcd(cycle_gcd,pom);
    }

    map<ll,ll>mapa;
    for(int i=0;i<edges.size();i++){
        if(hval[i]==0)continue;
        mapa[hval[i]]+=edges[i].w;
    }

    ll path_gcd=0;
    for(auto it=mapa.begin();it!=mapa.end();it++){
        path_gcd=__gcd(path_gcd,it->ss);
    }
    path_gcd=__gcd(path_gcd,cycle_gcd);
    if(cycle_gcd%(path_gcd*2)==0)path_gcd*=2;

    printf("%lld\n",path_gcd);


    return 0;
}
