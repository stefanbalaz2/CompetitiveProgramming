#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=5e5+10;
ll x,y,z,p[maxn];
int n,m;
map<pii,int>mapa;
ll ask(int a,int b){
    if(mapa.find({a,b})!=mapa.end())return mapa[{a,b}];
    ll pom=min(a,b)*x+max(a,b)*y;
    pom%=z;
    if(pom<p[a]+p[b])return 0;
    return 1;
}

int nxt(int x){
    if(x==n)return 1;
    return x+1;
}
int prv(int x){
    if(x==1)return n;
    return x-1;
}

vector<pii>rez;
unordered_set<int>diff,same;
int adj[maxn][2];

bool get_same(int i){

    int nv,pv;
    nv=ask(i,adj[i][1]);
    pv=ask(i,adj[i][0]);
    if(nv==pv){
        return 1;
    }
    else{
        return 0;
    }

}

int go(int cn){

    if(cn==1)return 0;

    if(diff.size()==0){

        int prv=-1;
        int rc=-1;
        vector<int>pp;
        for(unordered_set<int>::iterator it=same.begin();it!=same.end();it++){
            pp.pb((*it));
        }
        sort(pp.begin(),pp.end());
        for(int i=0;i<pp.size();i++){
            int id=pp[i];
            if(prv!=-1){
                rez.pb({prv,id});
                rc=ask(prv,id);
            }
            prv=id;
        }
        return rc;
    }

    int x=(*diff.begin());
    diff.erase(x);

    diff.erase(adj[x][0]);
    diff.erase(adj[x][1]);
    same.erase(adj[x][0]);
    same.erase(adj[x][1]);

    adj[adj[x][0]][1]=adj[x][1];
    adj[adj[x][1]][0]=adj[x][0];

    if(get_same(adj[x][0]))same.insert(adj[x][0]);
    else diff.insert(adj[x][0]);
    if(get_same(adj[x][1]))same.insert(adj[x][1]);
    else diff.insert(adj[x][1]);

    ///printf("%d XXX\n",x);

    int cl=go(cn-1);


    diff.erase(adj[x][0]);
    diff.erase(adj[x][1]);
    same.erase(adj[x][0]);
    same.erase(adj[x][1]);

    adj[adj[x][0]][1]=x;
    adj[adj[x][1]][0]=x;

    if(get_same(adj[x][0]))same.insert(adj[x][0]);
    else diff.insert(adj[x][0]);
    if(get_same(adj[x][1]))same.insert(adj[x][1]);
    else diff.insert(adj[x][1]);


    if(ask(x,adj[x][0])==cl)rez.pb({x,adj[x][0]});
    else rez.pb({x,adj[x][1]});

    return cl;

}

int main(){

    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        mapa[{a,b}]=c;
        mapa[{b,a}]=c;
    }
    scanf("%lld %lld %lld",&x,&y,&z);
    for(int i=1;i<=n;i++)scanf("%lld",&p[i]);

    for(int i=1;i<=n;i++){
        adj[i][0]=prv(i);
        adj[i][1]=nxt(i);

        int nv,pv;
        nv=ask(i,nxt(i));
        pv=ask(i,prv(i));
        if(nv==pv){
            same.insert(i);
        }
        else{
            diff.insert(i);
        }
    }

    go(n);

    for(int i=0;i<rez.size();i++)printf("%d %d\n",rez[i].ff,rez[i].ss);

    return 0;
}
