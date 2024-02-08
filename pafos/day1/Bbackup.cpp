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

ll n,m[maxn],len[maxn],xp[maxn][maxm],yp[maxn][maxm],pw3[15],ind[maxn][maxm];
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

    ///if(n>4)return 214;



    /// verovatno ovde paziti da li je podskup sa leve a ovaj koji stavljam sa desne itd
    /// mozda i ne

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


    ///printf("%d %d %d %d | %lld  DPCOST\n",);

    return a;
}

ll niz[177147][15];
ll lpos_prek[177147],rpos_prek[177147],leftmask_prek[177147],rightmask_prek[177147],acmask_prek[177147];
ll tmp[177147];
ll get_g(int i,int j,int mask){


    /// posebno za i==n i i==n+1

    if(mask&(1<<vect[i].ff))return inf;
    if(mask&(1<<vect[j].ff))return inf;
    int x1=xp[vect[i].ff][vect[i].ss];
    int x2=xp[vect[j].ff][vect[j].ss];
    int l1=len[vect[i].ff];
    int l2=len[vect[j].ss];
    if(x1+l1>x2 || x1==x2)return inf;
    if(g[i][j][mask]!=-1){
       //if(g[i][j][mask]!=inf)printf("%d %d %d | %lld GG\n",i,j,mask,g[i][j][mask]);
        return g[i][j][mask];
    }

    /// prodjes kroz 3maske sve i zabelezis rezultate, 3maske ne smeju imati i ili j

    for(int mask=0;mask<pw3[n];mask++){
        tmp[mask]=inf;
        g[i][j][acmask_prek[mask]]=inf;
    }

    tmp[0]=yp[vect[j].ff][vect[j].ss];

    for(int ii=0;ii<pw3[n];ii++){


        if(niz[ii][vect[j].ff]!=0 || niz[ii][vect[i].ff]!=0){
            tmp[ii]=inf;
            continue;
        }

        int leftmask=leftmask_prek[ii];
        int rightmask=rightmask_prek[ii];
        ll lpos=xp[vect[i].ff][vect[i].ss]+len[vect[i].ff]+lpos_prek[ii];
        ll rpos=xp[vect[j].ff][vect[j].ss]+rpos_prek[ii];

        ///printf("%d | %d %d %d %d AAA\n",ii,leftmask,rightmask,lpos,rpos);

        if(i==48 && j==2 && acmask_prek[ii]==254){
            printf("%d %d | %lld\n",leftmask,rightmask,tmp[ii]);
        }

        if(lpos>rpos){
            tmp[ii]=inf;
            continue;
        }
        if(lpos+len[vect[j].ff]>rpos){
            continue;
        }

        for(int jj=0;jj<n;jj++){
            if(niz[ii][jj]==0){

                tmp[ii+pw3[jj]]=min(tmp[ii+pw3[jj]], tmp[ii]+get_dpcost(i,leftmask,jj,1));
                tmp[ii+2*pw3[jj]]=min(tmp[ii+2*pw3[jj]], tmp[ii]+get_dpcost(j,rightmask,jj,0));

            }
        }


    }



    for(int ii=0;ii<pw3[n];ii++){
        int acmask=acmask_prek[ii];
        g[i][j][acmask]=min(tmp[ii],g[i][j][acmask]);
    }

    //if(g[i][j][mask]!=inf)printf("%d %d %d | %lld GG\n",i,j,mask,g[i][j][mask]);
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
                    ///printf("%d %d | %d %d | %lld  COST\n ",i,mask,j,sub,get_g(i,j,sub^(1<<j)));
                }
            }
        }
        a=min(a,get_g(i,vect.size()-1,sub)+get_f(vect.size()-1,mask^sub));
        if(sub==0)break;/// MOZDA OVDE GRESKA
    }


    ///printf("%d %d  | %lld   FFF\n",i,mask,a);

    return a;
}

int main(){

    ///printf("%d %d %d AAA\n",sizeof(dpcost),sizeof(f),sizeof(g));

    freopen("test.txt","r",stdin);
    freopen("moj2.txt","w",stdout);

    memset(dpcost,-1,sizeof(dpcost));
    memset(f,-1,sizeof(f));
    memset(g,-1,sizeof(g));

    pw3[0]=1;
    for(int i=1;i<=14;i++)pw3[i]=pw3[i-1]*3;

    scanf("%lld",&n);

    for(int i=0;i<n;i++){

        scanf("%lld %lld",&m[i],&len[i]);

        for(int j=0;j<m[i];j++){
            scanf("%lld %lld",&xp[i][j],&yp[i][j]);
            vect.pb({i,j});
            ind[i][j]=vect.size()-1;
        }
    }


    for(int ii=0;ii<pw3[n];ii++){
       /// printf("%d AAA\n",pw3[n]);
        int pt=0;
        int mask2=ii;
        int acmask=0;
        for(int jj=0;jj<n;jj++){
            niz[ii][pt++]=mask2%3;
            if(mask2%3){
                acmask|=(1<<jj);
            }
            mask2/=3;
        }
        acmask_prek[ii]=acmask;
        for(int jj=0;jj<n;jj++){
            if(niz[ii][jj]==1){
                lpos_prek[ii]+=len[jj];
                leftmask_prek[ii]|=(1<<jj);
            }
            else if(niz[ii][jj]==2){
                rpos_prek[ii]-=len[jj];
                rightmask_prek[ii]|=(1<<jj);
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
