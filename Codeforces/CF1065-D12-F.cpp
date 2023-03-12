/*

    idea: https://codeforces.com/blog/entry/62411


*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e6+10;

int n,par[maxn],sz[maxn],color[maxn],lefft[maxn],k,sum,cnt[maxn],rez;
vector<int>vect[maxn];

void reset_dsu(){

    for(int i=1;i<=n;i++){

        par[i]=i;
        sz[i]=1;

    }
}

int root(int x){
    if(par[x]==x)return x;
    else return par[x]=root(par[x]);
}

int join(int x,int y){

    x=root(x);
    y=root(y);

    if(sz[x]<sz[y])swap(x,y);

    par[y]=x;
    sz[x]+=sz[y];

    return x;
}

void go(int x,int prv){

    int child=0;
    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        if(id==prv)continue;

        child++;
        go(id,x);

        ///printf("%d %d | %d %d \n",x,id,color[id],lefft[id]);

        if(color[id]==0)continue;
        if(lefft[id]==0)continue;

        if(color[x]==0){
              ///  printf("USO\n");
            color[x]=color[id];
            lefft[x]=lefft[id]-1;
        }
        else{
            color[x]=join(color[x],color[id]);
            lefft[x]=max(lefft[x],lefft[id]-1);
        }

        ///printf("%d ADSA\n",color[x]);

    }

   /// printf("%d %d %d COLOR\n",x,color[x],sz[color[x]]);

    if(child==0){
        color[x]=x;
        lefft[x]=k;
        ///printf("%d %d COLOR\n",x,color[x]);
        return;
    }

}
void go2(int x,int prv){

    if(color[x]!=0){
        cnt[root(color[x])]++;
        if(cnt[root(color[x])]==1)sum+=sz[root(color[x])];
        rez=max(rez,sum);
    }

    ///printf("%d %d ADSA\n",x,sum);

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        go2(id,x);
    }

    if(color[x]!=0){
        cnt[root(color[x])]--;
        if(cnt[root(color[x])]==0)sum-=sz[root(color[x])];
    }
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);

    reset_dsu();

    for(int i=2;i<=n;i++){
        int p;
        scanf("%d",&p);
        vect[i].pb(p);
        vect[p].pb(i);
    }

    go(1,0);
    go2(1,0);

    printf("%d\n",rez);

    return 0;
}
