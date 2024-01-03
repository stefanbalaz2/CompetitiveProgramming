/**

    problem: https://codeforces.com/gym/100513/problem/L

    obavezno procisti graf od nonreachable nodeova jer ces dobiti RTE ili MLE ili neko drugo sranje

*/

#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=2e5+10;
int n,m;
vector<int>bucket[maxn],rg[maxn],children[maxn],dtree[maxn];
vector<pii>vect[maxn],realv[maxn];
int arr[maxn],rev[maxn],sdom[maxn],dom[maxn],idom[maxn],label[maxn],dpar[maxn],tmm;
int st[maxn],en[maxn];

int root(int x){

    if(x==dpar[x])return label[x];

    int v=root(dpar[x]);
    if(sdom[v]<sdom[label[x]])label[x]=v;
    dpar[x]=dpar[dpar[x]];
    return label[x];
}
void join(int x,int y){
    dpar[y]=x;
}
void dfs(int x,int prv){

    tmm++;
    arr[x]=tmm;
    rev[tmm]=x;
    int y=arr[x];
    sdom[y]=y;
    label[y]=y;
    dpar[y]=y;
    bucket[y].clear();
    if(prv!=0)
        children[arr[prv]].pb(y);


    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        if(arr[id]==0)dfs(id,x);
        rg[arr[id]].pb(y);
    }

}
int procisti_graf(int x){

    int start=x;

    queue<int>q;
    vector<int>pos(n+1,0),nmp(n+1);
    int cnt=0;
    q.push(x);
    pos[x]=1;
    while(q.size()){

        x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i].ff;
            if(pos[id])continue;
            q.push(id);
            pos[id]=1;
        }

    }

    for(int i=1;i<=n;i++){
        if(pos[i])
            nmp[i]=++cnt;
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<vect[i].size();j++){
            int a=i;
            int b=vect[i][j].ff;
            if(pos[a]==0 || pos[b]==0)continue;

            realv[nmp[a]].pb({nmp[b],vect[i][j].ss});
        }
    }

    for(int i=1;i<=cnt;i++)vect[i]=realv[i];
    n=cnt;
    return nmp[start];
}
void build(int x){

    x=procisti_graf(x);

    dfs(x,0);

    for(int i=n;i>=1;i--){

        for(int j=0;j<rg[i].size();j++){
            int id=rg[i][j];
            sdom[i]=min(sdom[i],sdom[root(id)]);
        }

        bucket[sdom[i]].pb(i);

        for(int j=0;j<bucket[i].size();j++){
            int id=bucket[i][j];
            int v=root(id);
            if(sdom[v]==i)dom[id]=i;
            else dom[id]=v;
        }

        for(int j=0;j<children[i].size();j++)
            join(i,children[i][j]);

    }

    for(int i=2;i<=n;i++){
        if(sdom[i]==dom[i])idom[i]=dom[i];
        else idom[i]=idom[dom[i]];
    }

    for(int i=2;i<=n;i++)
        dtree[rev[idom[i]]].pb(rev[i]);


}
void go(int x){

    st[x]=++tmm;
    for(int i=0;i<dtree[x].size();i++){
        go(dtree[x][i]);
    }
    en[x]=++tmm;

}
bool insub(int x,int y){
    if(st[y]<=st[x] && en[x]<=en[y])return true;
    return false;
}

int main(){


   /// freopen("test2.txt","r",stdin);


    while(scanf("%d %d",&n,&m)==2){

        tmm=0;
        for(int i=1;i<=n;i++){
            vect[i].clear();
            rg[i].clear();
            children[i].clear();
            arr[i]=0;
            dtree[i].clear();
            realv[i].clear();
        }
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            vect[u].pb({v,i});
        }

        build(1);

        go(1);
        set<int>rez;
        for(int i=1;i<=n;i++){
            for(int j=0;j<vect[i].size();j++){
                int v=vect[i][j].ff;
                int id=vect[i][j].ss;

                if(insub(i,v)){}
                else rez.insert(id);
            }
        }

        printf("%d\n",rez.size());
        for(auto it=rez.begin();it!=rez.end();it++)printf("%d ",(*it));
        printf("\n");

    }


    return 0;
}
