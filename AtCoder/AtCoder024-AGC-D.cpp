/*

    idea:https://img.atcoder.jp/agc024/editorial.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll>pii;
const int maxn=100+10;
int p[maxn],n;
vector<int>vect[maxn];
ll d[maxn];
pii nadji(int x,int prv){

    p[x]=prv;
    pii ret={1,x};
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        ret=max(ret,nadji(id,x));
    }

    return {ret.ff+1,ret.ss};
}
vector<int> get_dia(){

    int x=nadji(1,0).ss;
    int y=nadji(x,0).ss;

    vector<int>ret;
    while(y!=x){
        ret.pb(y);
        y=p[y];
    }
    ret.pb(y);

    return ret;
}
void go(int x,int prv,int lvl){

    ll child=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        child++;

        go(id,x,lvl+1);
    }
    d[lvl]=max(d[lvl],child);
}
ll singlec(int x){

    memset(d,-1,sizeof(d));
    go(x,0,1);

    ll ret=1;
    for(int i=1;i<=n;i++){
        if(d[i]<=0)continue;
        ret*=d[i];
    }

    return ret;
}
ll doublec(int x,int y){

    memset(d,-1,sizeof(d));
    go(y,x,1);
    go(x,y,1);

    ll ret=1;
    for(int i=1;i<=n;i++){
        if(d[i]<=0)continue;
        ret*=d[i];
    }

    return ret*2;
}

int main(){

    ///freopen("test2.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<n;i++){

        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    vector<int>dia=get_dia();

    if(dia.size()%2){

        int c=dia[dia.size()/2];
        ll ret=singlec(dia[dia.size()/2]);
        for(int i=0;i<vect[c].size();i++){
            int id=vect[c][i];
            ret=min(ret,doublec(c,id));
        }

        printf("%d %lld\n",dia.size()/2+1,ret);

    }
    else{
        printf("%d %lld\n",dia.size()/2,doublec(dia[dia.size()/2],dia[dia.size()/2-1]));
    }


    return 0;
}
