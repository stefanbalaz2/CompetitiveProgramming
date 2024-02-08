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

typedef unsigned long long ull;
using int128=__int128_t;
const int mb=64;
const ull maxa=(((int128)1)<<mb)-1;

const int maxn=1e4+10;
vector<int>vect[maxn],rv[maxn];

struct binum{

    vector<ull>a;

    int size(){return a.size();}
    ull& operator [](int x){
        return a[x];
    }

    binum operator +(binum b){

        binum ret=(*this);
        ret.a.resize(max(a.size(),b.a.size()));
        b.a.resize(ret.size());

        ull coef=0;
        for(int i=0;i<ret.size();i++){

            int128 p0=(int128)ret[i]+b[i]+coef;

            if(p0>maxa)coef=1;
            else coef=0;

            ret[i]=(p0&maxa);
        }
        if(coef)ret.a.pb(1);

        return ret;
    }

    binum pw2(){
        binum ret=(*this);

        ull coef=0;
        for(int i=0;i<ret.size();i++){

            int128 p=(((int128)ret[i])<<1);

            ret[i]=(p&maxa);
            ret[i]|=coef;

            if(p>maxa)coef=1;
            else coef=0;
        }
        if(coef)ret.a.pb(1);

        return ret;
    }

    int get_mb(){

        if(a.size()==0)return -1;

        int ret=(a.size()-1)*mb;

        int lst=-1;
        for(int i=0;i<mb;i++){
            if( (((ull)1)<<i)&a.back() )lst=i;
        }

        return ret+lst;
    }


}niz[maxn];

int a[maxn],pos[maxn],n,m;

void dfs(int x,vector<int>&stek){

    pos[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        dfs(id,stek);
    }

    stek.pb(x);

}

int main(){

    ///freopen("test.txt","r",stdin);


    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]==0){}
        else niz[i].a.pb(a[i]);
    }
    for(int j=1;j<=m;j++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[v].pb(u);
        rv[u].pb(v);
    }

    vector<int>stek;
    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        dfs(i,stek);
    }


    int lst=-1;
    int pom2=0;
    for(int i=0;i<stek.size();i++){
        int id=stek[i];
        for(int j=0;j<rv[id].size();j++){
            int id2=rv[id][j];
            niz[id2]=niz[id2]+niz[id].pw2();
        }
        vector<ull>pomp;
        if(i<stek.size()-1)niz[id].a.swap(pomp);
        lst=id;
    }

    int pom=niz[lst].get_mb();

    printf("%d\n",pom+1);

    return 0;
}
