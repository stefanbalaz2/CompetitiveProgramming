
#include <bits/stdc++.h>
using namespace std;

void dfs(int x,int parent,int level){

    p[x]=parent;
    lvl[x]=level;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==parent)continue;

        dfs(id,x,level+1)
    }

}

void prekalkulacija(){

    for(int i=1;i<=n;i++){
        dp[i][0]=p[i];
    }

    int h=log2(n)+2;

    for(int i=1;i<=h;i++){
        for(int j=1;j<=n;j++){
            dp[j][i]=dp[ dp[j][i-1] ][i-1];
        }
    }

}

int lca(int x,int y){

    int h=log2(n);


    if(lvl[x]<lvl[y])swap(x,y);

    for(int i=h;i>=0;i--){
        if( lvl[dp[x][i]]>=lvl[y] ){
            x=dp[x][i];
        }
    }

    if(x==y)return x;

    for(int i=h;i>=0;i--){

        if(dp[x][i]==dp[y][i])continue;

        x=dp[x][i];
        y=dp[y][i];
    }

    return dp[x][0];
}

int main() {


    scanf("%d",&n);
    for(int i=1;i<n;i++){

        int u,v;
        scanf("%d %d",&u,&v);

        vect[u].pb(v);
        vect[v].pb(u);
    }

    /// root = 1
    dfs(1,0,1);

    prekalkulacija();

}
