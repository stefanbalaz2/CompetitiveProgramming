/**

    problem: https://www.codechef.com/problems/GRAPHCNT?tab=statement

    OBAVEZNO PROCISTI GRAF OD NONREACHABLE NODES JER CES DOBITI MLE/RTE
    
*/

#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=1e5+10;
int n,m;
vector<int>vect[maxn],rg[maxn],bucket[maxn],dtree[maxn],children[maxn];
int dsu[maxn],arr[maxn],rev[maxn],sdom[maxn],dom[maxn],idom[maxn],label[maxn],p[maxn],tmm;

int Find(int x){

    if(x==dsu[x])return label[x];

    int v=Find(dsu[x]);

    if(sdom[label[v]]<sdom[label[x]])
        label[x]=v;

    dsu[x]=dsu[dsu[x]];
    return label[x];
}
void Union(int x,int y){
    dsu[y]=x;
}
void dfs(int x,int prv){

    tmm++;
    rev[tmm]=x;
    arr[x]=tmm;
    label[arr[x]]=arr[x];
    sdom[arr[x]]=arr[x];
    dsu[arr[x]]=arr[x];
    if(prv!=0){
        children[arr[prv]].pb(arr[x]);
        p[arr[x]]=arr[prv];
    }
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(!arr[id])dfs(id,x);
        rg[arr[id]].pb(arr[x]);
    }

}
void calc_dominator(int x){

    dfs(x,0);

    for(int i=n;i>=1;i--){

        for(int j=0;j<rg[i].size();j++){
            int id=rg[i][j];
            int v=sdom[Find(id)];
            sdom[i]=min(sdom[i],v);
        }

        bucket[sdom[i]].pb(i);

        for(int j=0;j<bucket[i].size();j++){
            int id=bucket[i][j];
            int v=Find(id);

            if(sdom[v]<sdom[id])dom[id]=v;
            else dom[id]=sdom[id];
        }

        for(int j=0;j<children[i].size();j++)
            Union(i,children[i][j]);

    }

    for(int i=2;i<=n;i++){
        if(dom[i]==sdom[i])idom[i]=sdom[i];
        else idom[i]=idom[dom[i]];
    }

    for(int i=2;i<=n;i++)
        dtree[rev[idom[i]]].pb(rev[i]);


}

int sz[maxn];
void go(int x){

    sz[x]=1;
    for(int i=0;i<dtree[x].size();i++){
        int id=dtree[x][i];
        go(id);
        sz[x]+=sz[id];
    }

}


int main(){


    ///freopen("test2.txt","r",stdin);


    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
    }

    calc_dominator(1);

    ll rez=0;
    go(1);

    ll sum=1;
    for(int i=0;i<dtree[1].size();i++){
        int id=dtree[1][i];
        rez+=(ll)sz[id]*sum;
        sum+=sz[id];
    }

    printf("%lld\n",rez);

    return 0;
}
