/*

    idea:    https://codeforces.com/blog/entry/83553

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
ll rez;
const int maxn=210;
const int maxm=maxn*maxn;
struct edge{
    int a,b,flow;
};
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int flow,sink[maxm],par[maxm],n,a[maxn][maxn],ind[maxn][maxn],cnt;
vector<edge>e;
vector<int>vect[maxm],p[maxm],pos;
void rev(int x){
    if(p[x].size()==0)return;
    int id=p[x].back();
    p[x].pop_back();
    e[id].flow^=1;
    e[id^1].flow^=1;
    rev(e[id].a);
}
void reverse_flow(int x){
    while(p[x].size())rev(x),flow--;
}
int bfs(){

    queue<int>q;

    memset(par,-1,sizeof(par));
    for(int i=0;i<pos.size();i++)q.push(pos[i]),par[pos[i]]=-2;


    int ret=-1;
    while(q.size()){

        int x=q.front();
        q.pop();
        if(sink[x]){
            ret=x;
            break;
        }


        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(e[id].flow || par[e[id].b]!=-1)continue;

            q.push(e[id].b);
            par[e[id].b]=id;
        }
    }

    if(ret==-1)return 0;

    while(par[ret]!=-2){
        int id=par[ret];

        p[ret].pb(id);

        e[id].flow^=1;
        e[id^1].flow^=1;

        ret=e[id].a;
    }

    return 1;
}
void flow_it(){
    while(bfs())flow++;
}
void add_edge(int x,int y){

    vect[x].pb(e.size());
    e.pb({x,y,0});

    vect[y].pb(e.size());
    e.pb({y,x,1});
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d",&n);
    vector<pii>cand;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            cnt++;
            ind[i][j]=cnt;
            if(a[i][j]>0){
                cand.pb({a[i][j],cnt});
                sink[cnt]=1;
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){

            if(a[i][j]==-1)continue;

            for(int k=0;k<4;k++){
                int idx=i+dx[k];
                int idy=j+dy[k];
                if(idx<0 || idy<0 || idx>n && idy>n)continue;
                if(a[idx][idy]==-1)continue;

                add_edge(ind[i][j],ind[idx][idy]);
            }
        }

    }

    sort(cand.begin(),cand.end());


    int pt=0;
    while(pt<cand.size()){

        int currk=cand[pt].ff;

        while(pt<cand.size() && cand[pt].ff==currk){

            reverse_flow(cand[pt].ss);
            pos.pb(cand[pt].ss);
            sink[cand[pt].ss]=0;
            flow_it();
            pt++;

        }


        if(pt!=cand.size())
            rez+=(ll)flow*((ll)cand[pt].ff-currk);
    }

    printf("%lld\n",rez);

    return 0;
}
