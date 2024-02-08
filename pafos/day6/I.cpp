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

const int maxn=3e5+10;
int n,m,pos[maxn],cnt,col[maxn],niz[maxn];
vector<int>vect[3][maxn];


void dfs(int x,vector<int>&cand){

    pos[x]=1;
    cand.pb(x);
    for(int i=0;i<vect[0][x].size();i++){
        int id=vect[0][x][i];
        if(pos[id])continue;
        dfs(id,cand);
    }
}
void go1(int x,vector<int>&stek){

    pos[x]=1;
    for(int i=0;i<vect[1][x].size();i++){
        int id=vect[1][x][i];
        if(pos[id])continue;
        go1(id,stek);
    }

    stek.pb(x);
}
void go2(int x,int cnt){

    col[x]=cnt;
    ///printf("%d %d AAA\n",x,cnt);
    for(int i=0;i<vect[2][x].size();i++){
        int id=vect[2][x][i];
        if(col[id])continue;
        go2(id,cnt);
    }
}
void go_scc(){

    memset(pos,0,sizeof(pos));
    vector<int>stek;
    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        go1(i,stek);
    }

    while(stek.size()){
        int id=stek.back();
        stek.pop_back();
        if(col[id])continue;
        ///printf("%d STEK\n",id);
        cnt++;
        go2(id,cnt);
    }

}
int main(){

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,p;
        scanf("%d %d %d",&u,&v,&p);
        vect[0][u].pb(v);
        if(p==2){
            vect[1][u].pb(v);
            vect[2][v].pb(u);
        }
    }

    vector<int>cand;
    dfs(1,cand);

    go_scc();

    for(int i=1;i<=n;i++){
        ///printf("%d %d COL\n",i,col[i]);
        for(int j=0;j<vect[1][i].size();j++){
            int id=vect[1][i][j];
            if(col[i]!=col[id])niz[col[i]]=1;
        }
    }

    int e=0;
    for(int i=0;i<cand.size();i++){
        if(niz[col[cand[i] ]])e=1;
    }
    if(e)printf("Yes\n");
    else printf("No\n");

    return 0;
}
