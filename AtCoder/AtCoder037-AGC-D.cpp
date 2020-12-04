/*

    idea:   https://img.atcoder.jp/agc037/editorial.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll>pii;
const int maxn=200+10;
struct edge{
    int a,b,flow;
};
vector<edge>e;
vector<int>vect[maxn],rcols[maxn][maxn];
int source,sink,n,m,a[maxn][maxn],ind[maxn][maxn],col[maxn][maxn],level[maxn],start[maxn],rez[maxn*maxn],cnt,b[maxn][maxn],c[maxn][maxn];
pii rind[maxn*maxn],poc[maxn*maxn];
void add_edge(int x,int y){

    vect[x].pb(e.size());
    e.pb({x,y,0});

    vect[y].pb(e.size());
    e.pb({y,x,1});
}
void reset_flow(){

    source=0;
    sink=2*n+1;
    e.clear();
    for(int i=source;i<=sink;i++){
        vect[i].clear();
    }
}
int bfs(){

    memset(level,0,sizeof(level));
    level[source]=1;
    queue<int>q;
    q.push(source);

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].flow || level[e[id].b])continue;

            level[e[id].b]=level[x]+1;
            q.push(e[id].b);
        }

    }

    return level[sink];
}
int send_flow(int x,int flow){

    if(x==sink)return flow;

    for(;start[x]<vect[x].size();start[x]++){

        int id=vect[x][start[x]];

        if(e[id].flow==0 && level[x]+1==level[e[id].b]){

            int temp_flow=send_flow(e[id].b,flow);
            if(temp_flow){

                e[id].flow^=1;
                e[id^1].flow^=1;

                return temp_flow;

            }

        }

    }

    return 0;
}
void go(int column){

    reset_flow();

    for(int i=1;i<=n;i++){
        add_edge(source,i);
        add_edge(i+n,sink);
        for(int j=1;j<=n;j++){
            if(rcols[i][j].size()==0)continue;
            add_edge(i,j+n);
        }
    }

    while(bfs()){
        memset(start,0,sizeof(start));
        while(1){
            int pom=send_flow(source,1);
            if(pom==0)break;
        }
    }

    for(int i=1;i<=n;i++){

        int ret=-1;
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j];
            if(e[id].flow){
                ret=e[id].b-n;
                break;
            }
        }

        /// dopuni
        int pom=rcols[i][ret].back();
        rcols[i][ret].pop_back();

        rez[pom]=column;
    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            ind[i][j]=++cnt;
            col[i][j]=i;
            rind[cnt]={i,j};
            poc[a[i][j]]={i,j};
        }
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            rcols[i][rind[a[i][j]].ff].pb(a[i][j]);


    for(int i=1;i<=m;i++)
        go(i);


    for(int i=1;i<=n*m;i++){
        b[poc[i].ff][rez[i]]=i;
        c[rind[i].ff][rez[i]]=i;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
        printf("%d ",b[i][j]);
        printf("\n");
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
        printf("%d ",c[i][j]);
        printf("\n");
    }


    return 0;
}
