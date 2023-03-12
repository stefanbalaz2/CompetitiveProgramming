/**

    https://cses.fi/problemset/task/1694

    dinitz

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

ll inf=1e18;

struct edge{
    int u,v;
    ll f,c;
};
vector<edge>e;
const int maxn=1010;
vector<int>vect[maxn];
int start[maxn],level[maxn];
int s,t;
int n;

void add_edge(int u,int v,int cap){

    vect[u].pb(e.size());
    e.pb({u,v,0,cap});

    vect[v].pb(e.size());
    e.pb({v,u,cap,cap});
}
void go1(){

    memset(level,-1,sizeof(level));

    queue<int>q;
    q.push(s);
    level[s]=0;

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].c-e[id].f==0 || level[e[id].v]!=-1)continue;

            level[e[id].v]=level[x]+1;
            q.push(e[id].v);
        }

    }

}
ll send_flow(int x,ll flow){

    if(x==t)return flow;

    for(;start[x]<vect[x].size();start[x]++){

        int id=vect[x][start[x]];

        if(e[id].c>e[id].f && level[e[id].u]+1==level[e[id].v]){

            ll temp_flow=send_flow(e[id].v,min(flow,e[id].c-e[id].f));

            if(temp_flow){

                e[id].f+=temp_flow;
                e[id^1].f-=temp_flow;

                return temp_flow;
            }

        }

    }

    return 0;
}
ll get_flow(){

    s=1;
    t=n;
    ll ret=0;
    while(1){

        memset(start,0,sizeof(start));

        go1();
        if(level[t]==-1)break;

        ll pom=0;
        while(1){
            pom=send_flow(s,inf);
            if(pom==0)break;
            ret+=pom;
        }


    }

    return ret;

}
int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int m;
    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){

        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        add_edge(u,v,w);
    }

    printf("%lld\n",get_flow());


    return 0;
}
