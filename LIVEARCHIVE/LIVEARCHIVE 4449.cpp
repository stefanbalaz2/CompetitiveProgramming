/*

    not sure if the idea is correct or if the code gives AC

    idea: look at every edge and observe when can we add weight to it

        find all edges (u,v) such that all the paths from 1 to u are the same length
        and paths from v to N are the same length
        lets call these edges changeable

        among changeable edges, mark as unchangeable ones that can be reached by passing through
        a changeable edge

        now check if  the paths from 1 to N that dont pass changeable edges all have the same length
        if they dont, no solution
        if they do, lets call that length maxx

        if maxx is lower than the longest path that passes through a changeable edge, there is no solution
        else, add enough weight on all changeable edges to make the paths that go through them equal maxx

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=5e2+10;
int moze[maxn],ima[maxn],n,m;
pii dp[3][maxn];
vector<pii>rez,sol;
vector<pair<int,pii> >vect[maxn],rev[maxn];

pii solve1(int x){/// forward min/max

    if(dp[1][x]!=(pii){-1,-1})return dp[1][x];

    if(x==1){
        dp[1][x]={0,0};
        return dp[1][x];
    }

    dp[1][x]={1e9,-1e9};

    for(int i=0;i<rev[x].size();i++){
        int id=rev[x][i].ss.ff;
        int w=rev[x][i].ss.ss;

        if(moze[rev[x][i].ff])continue;

        dp[1][x].ff=min(dp[1][x].ff,solve1(id).ff+w);
        dp[1][x].ss=max(dp[1][x].ss,solve1(id).ss+w);
    }

    return dp[1][x];
}
pii solve2(int x){/// backward min/max

    if(dp[2][x]!=(pii){-1,-1})return dp[2][x];

    if(x==n){
        dp[2][x]={0,0};
        return dp[2][x];
    }

    dp[2][x]={1e9,-1e9};

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ss.ff;
        int w=vect[x][i].ss.ss;

        dp[2][x].ff=min(dp[2][x].ff,solve2(id).ff+w);
        dp[2][x].ss=max(dp[2][x].ss,solve2(id).ss+w);
    }

    return dp[2][x];
}

int dfs(int x){

    if(ima[x]!=-1)return ima[x];

    ima[x]=0;

    for(int i=0;i<rev[x].size();i++){

        int id=rev[x][i].ff;
        int xx=rev[x][i].ss.ss;

        ima[x]|=(dfs(xx));
        ima[x]|=(moze[id]);
    }

    return ima[x];
}

int main(){

    ///freopen("test.txt","r",stdin);

    int t=0;
    while(1){

        t++;
        printf("Case %d: ",t);
        scanf("%d %d",&n,&m);
        if(n==0 && m==0)break;

        for(int i=0;i<=n;i++)vect[i].clear(),rev[i].clear();

        for(int i=1;i<=m;i++){
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            vect[u].pb({i,{v,w}});
            rev[v].pb({i,{u,w}});
        }

        memset(dp,-1,sizeof(dp));
        memset(ima,-1,sizeof(ima));
        memset(moze,0,sizeof(moze));
        for(int i=1;i<=n;i++){
            solve1(i);
            solve2(i);

        }


        for(int i=1;i<=n;i++){

            for(int j=0;j<vect[i].size();j++){

                int id=vect[i][j].ff;
                int x=vect[i][j].ss.ff;

                if(solve1(i).ff==solve1(i).ss && solve2(x).ff==solve2(x).ss)moze[id]=1;

            }

        }

        for(int i=1;i<=n;i++){
            dfs(i);
        }

        int maxx=0;
        rez.clear();
        for(int i=1;i<=n;i++){
            for(int j=0;j<vect[i].size();j++){
                int id=vect[i][j].ff;
                if(dfs(i))moze[id]=0;

                if(moze[id]){
                    rez.pb({id,solve1(i).ff+vect[i][j].ss.ss+solve2(vect[i][j].ss.ff).ff });
                    maxx=max(maxx,solve1(i).ff+vect[i][j].ss.ss+solve2(vect[i][j].ss.ff).ff);
                }
            }
        }

        memset(dp[1],-1,sizeof(dp[1]));
        if((solve1(n).ff!=1e9)&&(solve1(n).ff!=solve1(n).ss || solve1(n).ff<maxx)){
            printf("No solution\n");
            continue;
        }

        if(solve1(n).ff!=1e9)maxx=solve1(n).ff;
        sol.clear();
        for(int i=0;i<rez.size();i++){

            int diff=maxx-rez[i].ss;
            if(diff==0)continue;

            sol.pb({rez[i].ff,diff});

        }

        printf("%d %d\n",sol.size(),maxx);
        for(int i=0;i<sol.size();i++)printf("%d %d\n",sol[i].ff,sol[i].ss);

    }


    return 0;
}
