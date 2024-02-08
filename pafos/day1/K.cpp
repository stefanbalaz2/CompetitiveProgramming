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

const int maxn=1010;
char a[maxn][maxn];
int n,m;
int ind[maxn][maxn];
vector<int>vect[maxn*maxn];

const int mb=19;
int h[2][510*510],dp[mb+1][510*510];
int dx[2]={2,0};
int dy[2]={0,2};
int dx2[2]={1,0};
int dy2[2]={0,1};
int cnt;

void go(int x,int prv,int ch,int c){

    h[c][x]=ch;
    ///printf("%d %d | %d\n",x,c,ch);
    if(c==0)dp[0][x]=prv;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        go(id,x,ch+1,c);
    }

}
void prek(){

    for(int i=0;i<=mb-1;i++)
        for(int j=1;j<=cnt;j++)
            dp[i+1][j]=dp[i][ dp[i][j] ];

}
int lca(int x,int y){

    if(h[0][x]>h[0][y])swap(x,y);

    for(int i=mb;i>=0;i--){
        if(h[0][dp[i][y]]<h[0][x])continue;
        y=dp[i][y];
    }

    if(x==y)return x;

    for(int i=mb;i>=0;i--){
        if(dp[i][y]==dp[i][x])continue;
        x=dp[i][x];
        y=dp[i][y];
    }

    return dp[0][x];

}

int main(){

    scanf("%d %d",&n,&m);

    for(int i=1;i<=n*2+1;i++){

        string s;
        cin>>s;
        for(int j=1;j<=2*m+1;j++){
            a[i][j]=s[j-1];
            if(i%2==0 && j%2==0)ind[i][j]=++cnt;
        }
    }

    vector<pii>cand;
    for(int i=2;i<=2*n+1;i+=2){
        for(int j=2;j<=2*m+1;j+=2){

            for(int k=0;k<2;k++){

                int idx=i+dx[k];
                int idy=j+dy[k];
                if(idx>2*n+1 || idy>2*m+1)continue;

                if(a[i+dx2[k]][j+dy2[k]]=='.'){
                    vect[ind[i][j]].pb( ind[idx][idy] );
                    vect[ind[idx][idy]].pb( ind[i][j] );
                }
                else{
                    cand.pb( { ind[i][j] , ind[idx][idy] } );
                }

            }

        }
    }

    int start=ind[2][2];
    int en=ind[2*n][2*m];
    go(start,0,1,0);
    go(en,0,1,1);
    prek();

    int rez=h[0][en];
    ///printf("%d %d AA\n",start,en);//
    for(int i=0;i<cand.size();i++){
        int u=cand[i].ff;
        int v=cand[i].ss;

        if(lca(u,en)==lca(v,en))continue;

        if(h[0][lca(u,en)]>h[0][lca(v,en)])swap(u,v);

        rez=max(rez, h[0][u]+h[1][v] );

    }
    printf("%d\n",rez);

    return 0;
}
