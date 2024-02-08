#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;

const int maxn=1e4+10;
const int maxk=510;

vector<int>dp[maxn][3],sdp[maxn][3];
vector<pair<pii,pair<pii,int>>>par[maxn][3];
vector<pair<int,pii>>p2[maxn][3];
vector<int>vect[maxn];
int n,k;
int dpar[maxn],deg[maxn];

void mrg(int x,int y){

    if(x==0){
        sdp[y][0]=dp[y][0];
        sdp[y][1]=dp[y][1];
        for(int i=1;i<sdp[y][1].size();i++)sdp[y][1][i]++;
        par[y][0].resize(sdp[y][0].size());
        par[y][1].resize(sdp[y][1].size());
        for(int i=0;i<=1;i++)
        for(int j=0;j<par[y][i].size();j++){
            par[y][i][j].ss.ff.ff=i;
            par[y][i][j].ss.ff.ss=j;
        }

        return;
    }

    int xn=max(sdp[x][0].size(),max(sdp[x][1].size(),sdp[x][2].size() ));
    int yn=max(dp[y][0].size(),max(dp[y][1].size(),dp[y][1].size() ));

    sdp[y][0].resize(xn+yn-1);
    sdp[y][1].resize(xn+yn-1);
    sdp[y][2].resize(xn+yn-1);
    par[y][0].resize(xn+yn-1);
    par[y][1].resize(xn+yn-1);
    par[y][2].resize(xn+yn-1);

    for(int fi=0;fi<=2;fi++){
        for(int fj=0;fj<=1;fj++){
            if(fi+fj>2)continue;
            for(int i=0;i<sdp[x][fi].size();i++){
                if(i==0 && fi>0)continue;
                for(int j=0;j<dp[y][fj].size();j++){
                    if(j==0 && fj>0)continue;
                    int val=sdp[x][fi][i]+dp[y][fj][j]+fj;
                    int flag=(fi==1 && fj==1);
                    val-=flag;

                    if(val>sdp[y][fi+fj][i+j-flag]){
                        sdp[y][fi+fj][i+j-flag]=val;
                        par[y][fi+fj][i+j-flag]={{fi,i},{{fj,j},x} };
                    }

                }
                if(fj==1)continue;
                for(int j=0;j<dp[y][1].size();j++){
                    if(j==0 && fj>0)continue;
                    int val=sdp[x][fi][i]+dp[y][1][j]+fj;
                    int flag=(fi==1 && fj==1);
                    val-=flag;

                    if(val>sdp[y][fi+fj][i+j-flag]){
                        sdp[y][fi+fj][i+j-flag]=val;
                        par[y][fi+fj][i+j-flag]={{fi,i},{{1,j},x} };
                    }

                }
            }
        }
    }

    sdp[y][0].resize(min((int)sdp[y][0].size(),k+1));
    sdp[y][1].resize(min((int)sdp[y][1].size(),k+1));
    sdp[y][2].resize(min((int)sdp[y][2].size(),k+1));

}
void go(int x,int pv){



    int prv=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==pv)continue;

        go(id,x);
        mrg(prv,id);
        prv=id;
    }

    if(prv==0){
        dp[x][0].resize(2);
        dp[x][1].resize(2);
        dp[x][0][1]=0;
        dp[x][1][1]=1;
        return;
    }
    for(int i=0;i<=2;i++){
        dp[x][i%2].resize(max(dp[x][i%2].size(),sdp[prv][i].size()));
        p2[x][i%2].resize(max(dp[x][i%2].size(),sdp[prv][i].size()));
        for(int j=0;j<sdp[prv][i].size();j++){
            if(dp[x][i%2][j]<sdp[prv][i][j]){
                p2[x][i%2][j]={prv,{i,j}};
            }
            dp[x][i%2][j]=max(dp[x][i%2][j],sdp[prv][i][j]);
        }
    }

}
set<int>nodes;
set<pii>edges;
void recover(int x,int up,int ck,int pv){

    int prv=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==pv)continue;
        prv=id;
    }

    if(prv==0){
        if(ck==1)nodes.insert(x);
        return;
    }

    int px=x;
    pair<int,pii>pom=p2[x][up][ck];
    x=pom.ff;
    up=pom.ss.ff;
    ck=pom.ss.ss;

    while(x!=0){
        recover(x,par[x][up][ck].ss.ff.ff,par[x][up][ck].ss.ff.ss,px);

        if(up!=par[x][up][ck].ff.ff){
            nodes.insert(x);
            nodes.insert(px);
            edges.insert({px,x});
        }

        pair<pii,pair<pii,int>>pom=par[x][up][ck];

        x=pom.ss.ss;
        up=pom.ff.ff;
        ck=pom.ff.ss;

    }

}
int root(int x){
    if(dpar[x]==x)return x;
    return dpar[x]=root(dpar[x]);
}
void join(int x,int y){
    x=root(x);
    y=root(y);
    if(x==y)return;
    dpar[x]=y;
}


int main(){

    ///freopen("test2.txt","r",stdin);

    while(1){
        scanf("%d %d",&n,&k);
        if(n==0 && k==0)break;

        nodes.clear();
        edges.clear();
        for(int i=1;i<=n;i++){
            vect[i].clear();
            deg[i]=0;
            dpar[i]=i;
            for(int j=0;j<=2;j++){
                sdp[i][j].clear();
                dp[i][j].clear();
                par[i][j].clear();
                p2[i][j].clear();
            }
        }

        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            vect[u].pb(v);
            vect[v].pb(u);
        }

        go(1,0);

        int x,up,ck;
        x=1;
        int mx=0;
        for(int i=0;i<dp[1][0].size();i++){
            if(mx<dp[1][0][i]){
                mx=dp[1][0][i];
                up=0;
                ck=i;
            }
        }
        for(int i=0;i<dp[1][1].size();i++){
            if(mx<dp[1][1][i]){
                mx=dp[1][1][i];
                up=1;
                ck=i;
            }
        }

        recover(x,up,ck,0);
        printf("%d\n",mx);

        for(set<pii>::iterator it=edges.begin();it!=edges.end();it++){
            join((*it).ff,(*it).ss);
            deg[(*it).ff]++;
            deg[(*it).ss]++;
        }

        vector<pii>rez;
        for(set<int>::iterator it=nodes.begin();it!=nodes.end();it++){
            int id=(*it);
            if(deg[id]==0){
                rez.pb({id,id});
            }
            else if(deg[id]==1){
                int pid=-1;
                for(int j=1;j<=n;j++){
                    if(j==id)continue;
                    if(root(id)==root(j) && deg[j]==1 && j<id){
                        pid=j;
                        break;
                    }
                }
                if(pid==-1)continue;
                rez.pb({id,pid});
            }
        }
        printf("%d\n",rez.size());
        for(int i=0;i<rez.size();i++)
            printf("%d %d\n",rez[i].ff,rez[i].ss);

    }

    return 0;
}
