/*

    idea: https://github.com/pranavjangir/CompetitiveProgramming/blob/master/CodeForces/CF101650-gym-I.cpp

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=2e5;

int pos[maxn],n,m,deg[maxn],p1[maxn];
vector<int>vect[maxn],cc[maxn];

void dfs(int x,int c){

    pos[x]=1;
    cc[c].pb(x);
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        if(pos[id])continue;

        dfs(id,c);

    }

}

int noc(){

    int ret=0;

    for(int i=1;i<=n;i++){
        if(pos[i] || p1[i]==0)continue;

        ret++;
        dfs(i,ret);
    }

    return ret;
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){

        int u,v;
        scanf("%d %d",&u,&v);

        if(u==0)u=++n;
        if(v==0)v=++n;

        deg[u]++;
        deg[v]++;

        vect[u].pb(v);
        vect[v].pb(u);

        p1[u]=1;
        p1[v]=1;

    }

    int nc=noc();

    if(nc>1){

        int ret=nc;

        for(int i=1;i<=nc;i++){

            int big=0;
            int odd=0;

            for(int j=0;j<cc[i].size();j++){
                int id=cc[i][j];
                if(deg[id]%2)odd++;
                if(deg[id]>2)big++;
            }

            ///printf("%d %d AAAA\n",odd,big);

            if(odd==0 && big==0)ret+=1;
            else if(odd!=0)ret+=odd/2+big-1;
            else ret+=big;

        }

        printf("%d\n",ret);

    }
    else{

        int big=0;
        int odd=0;
        for(int i=1;i<=nc;i++){

            ///printf("GOTOV\n");
            for(int j=0;j<cc[i].size();j++){
                int id=cc[i][j];
                if(deg[id]%2)odd++;
                if(deg[id]>2)big++;

                ///printf("%d %d AA\n",id,deg[id]);

            }

        }
        printf("%d\n",odd/2+big);
    }


    return 0;
}
