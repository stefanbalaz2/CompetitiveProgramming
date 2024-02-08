#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=1e5+10;
vector<bool> dp[maxn];
vector<int>vect[maxn],g[maxn];
vector<pii>vect2[maxn];
int match[maxn],n,m;
bool pos[maxn];

int go_match(int x){

    pos[x]=1;

    for(int i=0;i<g[x].size();i++){
        int id=g[x][i];
        if(match[id]==-1){
            match[id]=x;
            return x;
        }
    }

    for(int i=0;i<g[x].size();i++){
        int id=g[x][i];
        if(pos[match[id]])continue;

        int pom=go_match(match[id]);
        if(pom==-1)continue;

        match[id]=x;
        return x;
    }
    return -1;
}
int unmatched_vert;
int do_kuhn(int n){

    int ret=0;
    unmatched_vert=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)pos[j]=0;
        if(go_match(i)==-1){
            if(i+1-ret>1)return ret;
            unmatched_vert=i;
            continue;
        }
        ret++;
    }
    return ret;
}
void go_dfs(int x,vector<int>&rez){

    pos[x]=1;
    rez.pb(x);
    for(int i=0;i<g[x].size();i++){
        int id=g[x][i];
        if(pos[match[id]])continue;
        go_dfs(match[id],rez);
    }

}
void calc(int x,vector<int>&cand,int &e){


    for(int i=1;i<=m;i++){

        for(int j=0;j<vect2[i].size();j++)g[j].clear();
        for(int j=0;j<vect2[i].size();j++){
            int id=vect2[i][j].ss;
            for(int k=0;k<cand.size();k++){
                int id2=cand[k];
                if(dp[id2][id] || vect2[ vect2[i][j].ff ].size()==1){
                    g[j].pb(k);
                }
            }
        }

        for(int j=0;j<cand.size();j++)match[j]=-1;

        int mtc=do_kuhn(vect2[i].size());
        if(mtc==vect2[i].size()){
            e=1;
            return;
        }
        if(mtc<vect2[i].size()-1){
            continue;
        }

        /// odradis dfs
        vector<int>rez;
        for(int j=0;j<vect2[i].size();j++)pos[j]=0;
        go_dfs(unmatched_vert,rez);

        for(int j=0;j<rez.size();j++){
            int id=rez[j];
            dp[x][vect2[i][id].ss^1]=1;
        }

    }

}
void go(int x,int prv,int &e){

    vector<int>cand;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        go(id,x,e);
        if(e)return;
        cand.pb(id);
    }

    calc(x,cand,e);

}

int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            vect[i].clear();
            vect2[i].clear();
            dp[i].clear();
        }
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            vect[u].pb(v);
            vect[v].pb(u);
        }

        scanf("%d",&m);
        int cnt=0;
        for(int i=1;i<m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            vect2[u].pb({v,cnt++});
            vect2[v].pb({u,cnt++});
        }
        for(int i=1;i<=n;i++)dp[i].resize(cnt);

        int e=0;
        go(1,0,e);

        if(e)printf("YES\n");
        else printf("NO\n");

    }

    return 0;
}
