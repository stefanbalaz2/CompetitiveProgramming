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

const int maxn=15;
const int maxm=65;

ll n,m[maxn],len[maxn],xp[maxn][maxm],yp[maxn][maxm],ind[maxn][maxm];
vector<pii>vect;


ll dpcost[maxm][1<<11][maxn][2],g[maxm][maxm][1<<11],f[maxm][1<<11];
ll inf=1e16;
ll get_func_cost(int x,ll pos){

    if(pos<xp[x][0] || pos>xp[x][m[x]-1])return inf;
    for(int j=1;j<m[x];j++){
        if(pos<=xp[x][j] && pos>=xp[x][j-1]){
            return (pos-xp[x][j-1])*((yp[x][j]-yp[x][j-1])/(xp[x][j]-xp[x][j-1]))+yp[x][j-1];
        }
    }
    return yp[x][0];
}
ll get_dpcost(int i,int mask,int x,int flag){
    /// i -> koji (func,point)
    /// mask -> koji ce biti uzeti
    /// x-> koji postavljas
    /// flag -> levo ili desno


    if(dpcost[i][mask][x][flag]!=-1)return dpcost[i][mask][x][flag];

    ll &a=dpcost[i][mask][x][flag];


    if(flag==0){

        int pos=xp[vect[i].ff][vect[i].ss];
        for(int j=0;j<n;j++)
            if((1<<j)&mask)pos-=len[j];

        pos-=len[x];
        a=get_func_cost(x,pos);
    }
    else{

        int pos=xp[vect[i].ff][vect[i].ss]+len[vect[i].ff];
        for(int j=0;j<n;j++)
            if((1<<j)&mask)pos+=len[j];

        a=get_func_cost(x,pos);
    }



    return a;
}


ll lpos[1<<11];
ll dp[maxm][1<<11][2];
ll get_dp(int i,int mask,int flag){

    if(dp[i][mask][flag]!=-1)return dp[i][mask][flag];

    ll &a=dp[i][mask][flag];
    a=(flag^1)*yp[vect[i].ff][vect[i].ss];


    ll pom=inf;
    for(int j=0;j<n;j++)
        if((1<<j)&mask)
            pom=min(pom, get_dpcost(i,mask^(1<<j),j,flag)+get_dp(i,mask^(1<<j),flag)-(flag^1)*yp[vect[i].ff][vect[i].ss] );


    if(mask==0)pom=0;
    a+=pom;


    return a;

}
ll get_g(int i,int j,int mask){



    if(mask&(1<<vect[i].ff))return inf;
    if(mask&(1<<vect[j].ff))return inf;
    int x1=xp[vect[i].ff][vect[i].ss];
    int x2=xp[vect[j].ff][vect[j].ss];
    int l1=len[vect[i].ff];
    int l2=len[vect[j].ss];
    if(x1+l1+lpos[mask]>x2 || x1==x2)return inf;
    if(g[i][j][mask]!=-1)return g[i][j][mask];


    g[i][j][mask]=inf;
    for(int sub=mask;;sub=((sub-1)&mask)){
        g[i][j][mask]=min(g[i][j][mask], get_dp(i,sub,1)+get_dp(j,mask^sub,0) );
        if(sub==0)break;
    }


    return g[i][j][mask];
}
ll get_f(int i,int mask){

    if(i==vect.size()-1){
        if(mask==0)return 0;
        else return inf;
    }
    if(f[i][mask]!=-1)return f[i][mask];

    ll &a=f[i][mask];
    a=inf;

    for(int sub=mask;sub>=0;sub=((sub-1)&mask)){
        for(int j=0;j<n;j++){
            if(sub&(1<<j)){
                for(int k=0;k<m[j];k++){
                    a=min(a,get_f(ind[j][k],mask^sub)+get_g(i,ind[j][k],sub^(1<<j)));
                }
            }
        }
        a=min(a,get_g(i,vect.size()-1,sub)+get_f(vect.size()-1,mask^sub));
        if(sub==0)break;
    }


    return a;
}

int main(){


    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    memset(dpcost,-1,sizeof(dpcost));
    memset(f,-1,sizeof(f));
    memset(dp,-1,sizeof(dp));
    memset(g,-1,sizeof(g));

    scanf("%lld",&n);

    for(int i=0;i<n;i++){

        scanf("%lld %lld",&m[i],&len[i]);

        for(int j=0;j<m[i];j++){
            scanf("%lld %lld",&xp[i][j],&yp[i][j]);
            vect.pb({i,j});
            ind[i][j]=vect.size()-1;
        }
    }


    for(int i=0;i<(1<<n);i++){
        for(int jj=0;jj<n;jj++){
            if(i&(1<<jj)){
                lpos[i]+=len[jj];
            }
        }

    }

    m[n]=1;
    len[n]=0;
    m[n+1]=1;
    len[n+1]=0;
    xp[n][0]=-1;
    yp[n][0]=0;
    xp[n+1][0]=5e8+10;
    yp[n+1][0]=0;
    vect.pb({n,0});
    ind[n][0]=vect.size()-1;
    vect.pb({n+1,0});
    ind[n+1][0]=vect.size()-1;

    printf("%lld\n",get_f(vect.size()-2, (1<<n)-1 ) );


    return 0;
}
