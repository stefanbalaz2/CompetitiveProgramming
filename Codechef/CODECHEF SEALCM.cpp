/*

    idea:https://discuss.codechef.com/t/sealcm-editorial/9099

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int>pii;
const int maxm=1010;

int mp[maxm],m,n,cs;
ll mod=1e9+7;

void prek(){

    for(int i=2;i<maxm;i++){
        if(mp[i])continue;

        for(int j=i;j<maxm;j+=i){
            if(mp[j])continue;
            mp[j]=i;
        }

    }

}

vector<int> fact(int x){

    vector<pii>cp;
    while(1){

        if(x==1)break;

        if(cp.size()==0 || cp.back().ff!=mp[x])cp.pb({mp[x],mp[x]});
        else cp[cp.size()-1].ss*=mp[x];

        x/=mp[x];
    }

    vector<int>ret;
    for(int j=0;j<cp.size();j++){
        ret.pb(cp[j].ss);
    }

    return ret;
}



void get_trans(ll trans[1<<4][1<<4],vector<int> &f){

    /// iz state reda u state kolone

    for(int i=0;i<(1<<f.size());i++){

        for(int j=0;j<(1<<f.size());j++){

            int e=0;
            int prod=1;
            vector<int>v2;
            for(int k=0;k<f.size();k++){
                int b1=((i&(1<<k))>0);
                int b2=((j&(1<<k))>0);

                if(!b2 && b1){
                    e=1;
                    break;
                }

                if(!b1 && b2)prod*=f[k];
                if(!b1 && !b2)v2.pb(f[k]);
            }
            if(e)continue;

            int pom=m;
            pom/=prod;

            for(int k=0;k<(1<<v2.size());k++){

                ll pom2=1;
                for(int k2=0;k2<v2.size();k2++)
                    if(k&(1<<k2))pom2*=v2[k2];

                ///printf("%d ",pom2);

                if(__builtin_popcount(k)%2)trans[i][j]-=pom/pom2;
                else trans[i][j]+=pom/pom2;

            }

        }
    }

}

ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }

    return ret;
}

void mul(ll a[1<<4][1<<4],ll b[1<<4][1<<4]){

    ll ret[1<<4][1<<4];
    memset(ret,0,sizeof(ret));

    int mb=cs;

    for(int i=0;i<mb;i++)
        for(int j=0;j<mb;j++)
            for(int k=0;k<mb;k++)
                ret[i][j]=(ret[i][j]+a[i][k]*b[k][j])%mod;

    for(int i=0;i<mb;i++)
        for(int j=0;j<mb;j++)
            a[i][j]=ret[i][j];
}

void step(ll base[1<<4][1<<4],ll pw){

    ll ret[1<<4][1<<4];
    memset(ret,0,sizeof(ret));
    int mb=cs;
    for(int i=0;i<mb;i++)
        ret[i][i]=1;


    while(pw){

        if(pw&1)mul(ret,base);

        mul(base,base);
        pw/=2;

    }

    for(int i=0;i<mb;i++)
        for(int j=0;j<mb;j++)
            base[i][j]=ret[i][j];

}

ll calc(int d){

    if(d==1)return step(m,n);

    vector<int>pom=fact(d);


    ll trans[1<<4][1<<4],ret[1<<4][1<<4];
    memset(ret,0,sizeof(ret));
    memset(trans,0,sizeof(trans));
    ret[0][0]=1;

    cs=(1<<pom.size());

    get_trans(trans,pom);

    step(trans,n);
    mul(ret,trans);

    return ret[0][(1<<pom.size())-1];

}

int main(){


    prek();

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        int l,r;
        scanf("%d %d %d %d",&n,&m,&l,&r);

        ll ret=0;
        for(int i=l;i<=r;i++)
            ret=(ret+calc(i))%mod;


        printf("%lld\n",ret);
    }


    return 0;
}
