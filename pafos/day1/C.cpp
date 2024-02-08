#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

struct edge{
    int a,b,flow,cap,cost;
};
vector<edge>e;
const int maxm=110;
const int maxn=maxm*maxm;
vector<int>vect[maxn];

int a[maxm][maxm],ind[maxm][maxm],sink,source,inf=1e9,cnt;
int pos[maxn],n,m,mask[500];
int dx[4]={0,0,1,1};
int dy[4]={0,1,0,1};

void add_edge(int a,int b,int cap,int cost){

    vect[a].pb(e.size());
    e.pb({a,b,0,cap,cost});

    vect[b].pb(e.size());
    e.pb({b,a,cap,cap,-cost});

}

int get_val(int x,int y){
    if(x<1 || y<1 || x>n || y>m)return -1;
    return a[x][y];
}
int get_mask(vector<pii>&a,int curr){
    int ret=0;
    for(int i=0;i<4;i++){
        int idx=a[curr].ff+dx[i];
        int idy=a[curr].ss+dy[i];
        if(get_val(idx,idy)==2)ret|=mask['S'];
        if(get_val(idx,idy)==3)ret|=mask['U'];
        if(get_val(idx,idy)==4)ret|=mask['T'];
    }
    return ret;
}
int get_neighbours(int x,vector<pii>&a){

    int curr=x;
    int ret=0;
    while(1){
        ret|=get_mask(a,curr);
        ///printf("%d %d -> %d val\n",a[curr].ff,a[curr].ss,get_val(a[curr].ff+1,a[curr].ss+1));
        int nxt=curr+1;
        if(nxt>=a.size())nxt=0;
        if(get_mask(a,curr)&get_mask(a,nxt))break;
        curr=nxt;
    }


    curr=x;
    while(1){
        ret|=get_mask(a,curr);
        ///printf("%d %d -> %d val\n",a[curr].ff,a[curr].ss,get_val(a[curr].ff+1,a[curr].ss+1));
        int nxt=curr-1;
        if(nxt<0)nxt=a.size()-1;
        if(get_mask(a,curr)&get_mask(a,nxt))break;
        curr=nxt;
    }

    return ret;
}
void block_nodes(vector<pii>&a){

    queue<int>q;
    memset(pos,0,sizeof(pos));
    for(int i=0;i<a.size();i++){
        q.push(ind[a[i].ff][a[i].ss]);
        pos[ind[a[i].ff][a[i].ss]]=1;
    }

    while(q.size()){

        int x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=e[vect[x][i]].b;
            if(pos[id])continue;
            pos[id]=1;
            q.push(id);
        }

    }

}


int pot[maxn],par[maxn];
int dist[maxn];
pii go_flow(){

    set<pii>st;
    for(int i=source;i<=sink;i++)dist[i]=inf;
    for(int i=source;i<=sink;i++)par[i]=-1;

    dist[source]=0;
    st.insert({0,source});

    while(st.size()){

        int x=(*st.begin()).ss;
        st.erase(st.begin());

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(pos[e[id].b] || e[id].flow==e[id].cap)continue;
            int w=pot[x]+e[id].cost-pot[e[id].b];

            if(dist[e[id].b]>dist[x]+w){
                st.erase({dist[e[id].b],e[id].b});
                dist[e[id].b]=dist[x]+w;
                par[e[id].b]=id;
                st.insert({dist[e[id].b],e[id].b});
            }

        }

    }

    if(par[sink]==-1)return {0,0};

    int curr=sink;
    pii ret={1,0};
    while(curr!=source){
        int id=par[curr];
        ret.ss+=e[id].cost;
        e[id].flow++;
        e[id^1].flow--;
        curr=e[id].a;
    }

    for(int i=sink;i>=source;i--)
        pot[i]=dist[i]-pot[source]+pot[i];

    return ret;
}
int go(){

    int flow=0;
    int cost=0;

    for(int i=1;i<=2;i++){
        pii pom=go_flow();
        if(pom.ff==0)break;
        flow+=pom.ff;
        cost+=pom.ss;
    }

    if(flow<2)return -1;
    return cost;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=1;j<=m;j++){

            if(s[j-1]=='.')a[i][j]=0;
            else if(s[j-1]=='#')a[i][j]=1;
            else if(s[j-1]=='S')a[i][j]=2;
            else if(s[j-1]=='U')a[i][j]=3;
            else if(s[j-1]=='T')a[i][j]=4;
        }
    }

    cnt=0;
    source=0;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)ind[i][j]=++cnt;

    sink=++cnt;

    for(int i=0;i<n;i++){
        for(int j=1;j<m;j++){

            int ptx=i+1;
            int pty=j;

            if(a[ptx][pty]==1 || a[ptx][pty+1]==1){
                add_edge(ind[i][j],ind[ptx][pty],inf,0);
                add_edge(ind[ptx][pty],ind[i][j],inf,0);
            }

        }
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<m;j++){

            int ptx=i;
            int pty=j+1;

            if(a[ptx][pty]==1 || a[ptx+1][pty]==1){
                add_edge(ind[i][j],ind[ptx][pty],inf,0);
                add_edge(ind[ptx][pty],ind[i][j],inf,0);
            }

        }
    }
    mask['T']=1;
    mask['S']=2;
    mask['U']=4;

    vector<pii>grpA,grpB,grpC,boundary;
    for(int i=1;i<m;i++)boundary.pb({0,i});
    for(int i=1;i<n;i++)boundary.pb({i,m});
    for(int i=m-1;i>=1;i--)boundary.pb({n,i});
    for(int i=n-1;i>=1;i--)boundary.pb({i,0});

    for(int i=0;i<boundary.size();i++){
        ///printf("%d %d | %d AAAA\n",boundary[i].ff,boundary[i].ss,get_neighbours(i,boundary));
        if(get_neighbours(i,boundary)==(mask['T']|mask['S']) )grpA.pb(boundary[i]);
        else if(get_neighbours(i,boundary)==(mask['U']|mask['S']) )grpB.pb(boundary[i]);
        else if(get_neighbours(i,boundary)==(mask['U']|mask['T']) )grpC.pb(boundary[i]);
    }

    /// povezi sa sink i source
    /// izbaci lose vertexe

    for(int i=0;i<grpB.size();i++){
        int id=ind[grpB[i].ff][grpB[i].ss];
        ///printf("%d %d B\n",grpB[i].ff,grpB[i].ss);
        add_edge(id,sink,inf,0);
    }
    for(int i=0;i<grpC.size();i++){
        int id=ind[grpC[i].ff][grpC[i].ss];
        ///printf("%d %d C\n",grpC[i].ff,grpC[i].ss);
        add_edge(source,id,inf,0);
    }
    block_nodes(grpA);

    int e=0;
    for(int i=0;i<grpB.size();i++){
        int id=ind[grpB[i].ff][grpB[i].ss];
        if(pos[id])e=1;
    }
    for(int i=0;i<grpC.size();i++){
        int id=ind[grpC[i].ff][grpC[i].ss];
        if(pos[id])e=1;
    }
    if(e){
        printf("-1\n");
        return 0;
    }


    int q;
    scanf("%d",&q);
    while(q--){

        int x,y;
        string s;
        cin>>x>>y>>s;

        if(s=="r"){
            add_edge(ind[x][y],ind[x-1][y],1,1);
            add_edge(ind[x-1][y],ind[x][y],1,1);
        }
        else{
            add_edge(ind[x][y],ind[x][y-1],1,1);
            add_edge(ind[x][y-1],ind[x][y],1,1);
        }

    }

    printf("%d\n",go());

    return 0;
}
