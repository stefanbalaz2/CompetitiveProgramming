/*

    idea: https://codeforces.com/blog/entry/7937

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=6410;
struct edge{
    int a,b,flow,cap,cost;
};
int sink,source,dp[maxn],pot[maxn],inf=1e9,p[maxn],n,m,a[100][100],pos[maxn];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
vector<int>vect[maxn];
vector<edge>e;
int get_num(int x,int y){
    return (x-1)*m+y;
}
void make_edge(int u,int v,int flow,int cost){

    vect[u].pb(e.size());
    e.pb({u,v,0,flow,cost});

    vect[v].pb(e.size());
    e.pb({v,u,flow,flow,-cost});
}
int dijkstra(int &ccost){

    queue<int>st;
    for(int i=source;i<=sink;i++){
        dp[i]=inf;
        p[i]=-1;
    }
    dp[source]=0;

    memset(pos,0,sizeof(pos));

    st.push(source);
    while(st.size()){

        int x=(st.front());
        st.pop();
        x[pos]=0;

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].cap==e[id].flow)continue;

            int cost=e[id].cost;
            if(dp[e[id].b]>dp[x]+cost){
                if(!pos[e[id].b])st.push(e[id].b);
                dp[e[id].b]=dp[x]+cost;
                p[e[id].b]=id;
            }
        }
    }

    int curr=sink;
    int minn=inf;
    while(curr!=source){
        int id=p[curr];
        if(id==-1)return 0;

        minn=min(minn,e[id].cap-e[id].flow);
        curr=e[id].a;
    }

    curr=sink;
    while(curr!=source){
        int id=p[curr];

        ccost+=minn*e[id].cost;

        e[id].flow+=minn;
        e[id^1].flow-=minn;

        curr=e[id].a;
    }

    if(dp[sink]==inf)return 0;
    return 1;
}
int mc(){

    int curr_cost=0;
    while(dijkstra(curr_cost)){}

    return curr_cost;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    source=0;
    sink=n*m+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);

    for(int i=1;i<=n;i++){

        for(int j=1;j<=m;j++){
            if((i+j)%2){make_edge(get_num(i,j),sink,1,0);continue;}


            make_edge(source,get_num(i,j),1,0);
            for(int k=0;k<4;k++){
                int idx=i+dx[k];
                int idy=j+dy[k];
                if(idx<=0 || idy<=0 || idx>n || idy>m)continue;

                if(a[idx][idy]==a[i][j])make_edge(get_num(i,j),get_num(idx,idy),1,0);
                else make_edge(get_num(i,j),get_num(idx,idy),1,1);
            }
        }
    }

    printf("%d\n",mc());

    return 0;
}
