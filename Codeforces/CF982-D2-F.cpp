/*

    idea: https://codeforces.com/blog/entry/59551

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10;
int pos[maxn],pos2[maxn],stek[maxn],br,niz[maxn],n,m,cnt[maxn],cc,e;
int inf=1e9;
vector<int>vect[maxn],cyc;
void go(int x){

    pos[x]=1;
    stek[++br]=x;
    pos2[x]=br;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos2[id]){
            for(int j=pos2[id];j<=br;j++)cyc.pb(stek[j]);
            e=1;
            return;
        }
        else if(pos[id])continue;

        go(id);
        if(e)return;
    }

    br--;
    pos2[x]=0;
}
int dist(int l,int r){

    if(l==-1 || r==-1 || l==inf || r==inf)return inf;

    if(l<=r)return r-l;
    else return cyc.size()-l+r;
}
int go2(int x,int i,int dep){


    if(pos2[x]!=-1)return pos2[x];
    if(pos[x]!=-1)return pos[x];

    pos[x]=inf;
    for(int j=0;j<vect[x].size();j++){
        int id=vect[x][j];

        if(pos[x]==-1)pos[x]=go2(id,i,dep+1);
        else if(dist(go2(id,i,dep+1),i)<dist(pos[x],i))pos[x]=go2(id,i,dep+1);
    }

    if(pos[x]==-1)pos[x]=inf;

    return pos[x];
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);


    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
    }

    for(int i=1;i<=n;i++){
        if(pos[i] || e)continue;
        go(i);
    }


    memset(pos,-1,sizeof(pos));
    memset(pos2,-1,sizeof(pos2));
    for(int i=0;i<cyc.size();i++)pos2[cyc[i]]=i;

    for(int i=0;i<cyc.size();i++){
        int x=cyc[i];
        int ret=-1;

        for(int j=0;j<vect[x].size();j++){
            int id=vect[x][j];
            if(pos2[id]==(i+1)%cyc.size())continue;

            if(ret==-1)ret=go2(id,i,0);
            else if(dist(go2(id,i,0),i)<dist(ret,i))ret=go2(id,i,0);
        }

        if(ret==-1 || ret==inf)continue;

        cc++;
        if(ret<=i){
            niz[ret]++;
            niz[i+1]--;
        }
        else{
            niz[ret]++;
            niz[cyc.size()]--;

            niz[0]++;
            niz[i+1]--;
        }
    }

    int pom=0;
    int cand=-1;
    for(int i=0;i<cyc.size();i++){
        pom+=niz[i];
        niz[i]=pom;

        if(pom==cc){
            cand=cyc[i];
        }
    }

    if(cand==-1){
        printf("-1\n");
        return 0;
    }

    memset(pos,0,sizeof(pos));
    memset(pos2,0,sizeof(pos2));
    br=0;
    pos[cand]=1;
    e=0;


    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        go(i);
        if(e)break;
    }

    if(e){
        printf("-1\n");
        return 0;
    }
    else printf("%d\n",cand);

	return 0;
}
