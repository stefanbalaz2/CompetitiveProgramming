/*
  
    idea: https://github.com/tfg50/Competitive-Programming/blob/master/LIVEARCHIVES/LIVEARCHIVE2937.cpp

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=210;
struct edge{
    int a,b,flow,cap;
};
int mfsum,n,degree[maxn],source,sink,m,u[maxn*5],v[maxn*5],w[maxn*5],level[maxn],start[maxn],inf=1e9;
vector<int>vect[maxn];
vector<edge>e;
void make_edge(int u,int v,int flow){

    vect[u].pb(e.size());
    e.pb({u,v,0,flow});

    vect[v].pb(e.size());
    e.pb({v,u,flow,flow});
}
bool make_graph(){

    int sum=0;
    mfsum=0;
    for(int i=1;i<=n;i++){
        if(degree[i]==0)continue;
        if(degree[i]%2)return false;
        sum+=degree[i];

        if(degree[i]<0){
            make_edge(i,sink,-degree[i]/2);
            mfsum-=degree[i]/2;
        }
        else make_edge(source,i,degree[i]/2);
    }
    if(sum)return false;

    for(int i=1;i<=m;i++){
        if(w[i])continue;
        make_edge(v[i],u[i],1);
    }
    return true;
}
bool bfs(){

    memset(level,0,sizeof(level));

    queue<int>q;
    q.push(source);
    level[source]=1;

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].flow==e[id].cap)continue;
            if(level[e[id].b])continue;

            level[e[id].b]=level[x]+1;
            q.push(e[id].b);
        }
    }

return level[sink];
}
int flow(int x,int curr_flow){

    if(x==sink)return curr_flow;

    for(;start[x]<vect[x].size();start[x]++){
        int id=vect[x][start[x]];

        if(e[id].flow==e[id].cap || level[x]+1!=level[e[id].b])continue;

        int temp_flow=flow(e[id].b,min(curr_flow,e[id].cap-e[id].flow));
        if(temp_flow){

            e[id].flow+=min(curr_flow,temp_flow);
            e[id^1].flow-=min(curr_flow,temp_flow);

            return temp_flow;
        }
    }

return 0;
}
int go(){

    int ret=0;
    while(bfs()){

        memset(start,0,sizeof(start));
        int curr_flow=0;
        while(curr_flow=flow(source,inf))ret+=curr_flow;
    }

return ret;
}
void reset(){

    for(int i=0;i<=n+1;i++){
        vect[i].clear();
        degree[i]=0;
    }
    e.clear();
}
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d %d",&n,&m);
        reset();
        source=0;
        sink=n+1;
        for(int i=1;i<=m;i++){
            scanf("%d %d %d",&u[i],&v[i],&w[i]);
            degree[u[i]]--;
            degree[v[i]]++;
        }

        if(!make_graph()){
            printf("impossible\n");
            continue;
        }

        if(go()!=mfsum)printf("impossible\n");
        else printf("possible\n");
    }


    return 0;
}
