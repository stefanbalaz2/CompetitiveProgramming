/*

    decompose the graph into simple cycles
    every cycle is like 1 number
    meaning our problem is just to find xor subset of those numbers which
    gives min value when xored with any path from 1 to n

    full editorial: https://codeforces.com/blog/entry/53986

*/
#include<bits/stdc++.h>
#define ss second
#define ff first
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10;
const int maxbit=60;
ll pref[maxn],niz[maxn*2];
int br,n,m,dep[maxn];
struct ss{
    int first,second;
    ll w;
};
vector<ss>vect[maxn];
void go(int x,int prv,ll curr){

    pref[x]=curr;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ss;
        if(prv==id)continue;

        ll w=vect[x][i].w;
        id=vect[x][i].ff;
        if(pref[id]!=-1){
            if(dep[x]<dep[id])continue;
            niz[++br]=(curr^pref[id]^w);
            continue;
        }

        dep[id]=dep[x]+1;
        go(id,vect[x][i].ss,curr^w);
    }

}
ll gauss(){

    int index=1;
    for(int i=maxbit;i>=0;i--){

        int id=-1;
        for(int j=index;j<=br;j++)
        if(niz[j]&(1ll<<i)){
            id=j;
            break;
        }
        if(id==-1)continue;

        swap(niz[index],niz[id]);

        for(int j=1;j<=br;j++){
            if(j==index)continue;
            if(niz[j]&(1ll<<i))niz[j]^=niz[index];
        }
        index++;
    }

    ll ret=0;
    for(int i=1;i<=br;i++)ret^=niz[i];

    return ret;
}
int msb(ll x){

    ll pom=1;
    int ret=0;
    while(pom<x){
        ret++;
        pom*=2;
    }
    if(pom>x)ret--;
    return ret;
}
int main(){

	///freopen("test.txt","r",stdin);
	///freopen("moj.txt","w",stdout);

    scanf("%d %d",&n,&m);
    memset(pref,-1,sizeof(pref));
    for(int i=1;i<=m;i++){
        int u,v;
        ll w;
        scanf("%d %d %lld",&u,&v,&w);
        vect[u].pb({v,i,w});
        if(u!=v)vect[v].pb({u,i,w});
    }

    go(1,0,0);

    gauss();

    ll pom=pref[n];

    for(int i=1;i<=br;i++){
        if(niz[i]==0)break;
        if((1ll<<msb(niz[i]))&pom)pom^=niz[i];
    }

    printf("%lld\n",pom);


	return 0;
}
