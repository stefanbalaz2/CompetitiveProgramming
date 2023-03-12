/*

    idea:https://codeforces.com/blog/entry/64928

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxk=100;
int k,n;
ll mod=998244353,m,trans[maxk][maxk],b[maxk],pwm[maxk][maxk];
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){
        if(pw&1)ret=(ret*base)%mod;
        base=(base*base)%mod;
        pw>>=1;
    }
return ret;
}
void mmul(ll a[][maxk],ll b[][maxk]){

    ll ret[maxk][maxk];
    memset(ret,0,sizeof(ret));

    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            for(int p=0;p<k;p++){
                ret[i][j]=(ret[i][j]+a[i][p]*b[p][j])%(mod-1);
            }
        }
    }

    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            a[i][j]=ret[i][j];

}
void step_mat(ll a[][maxk],ll pw){

    ll ret[maxk][maxk];
    memset(ret,0,sizeof(ret));

    for(int i=0;i<k;i++)ret[i][i]=1;

    while(pw){

        if(pw&1)mmul(ret,a);

        mmul(a,a);
        pw>>=1;
    }

    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            a[i][j]=ret[i][j];
}
vector<ll> factorise(ll x){

    vector<ll>ret;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            ret.pb(i);
            x/=i;
        }
    }
    if(x>1)ret.pb(x);

    unique(ret.begin(),ret.end());

    return ret;
}
ll primitive_root(ll x){

    ll phi=x-1;
    vector<ll>fact=factorise(phi);

    for(int i=2;i<=x;i++){
        int ok=1;
        for(int j=0;j<fact.size();j++){
            if(step(i,phi/fact[j])==1){
                ok=0;
                break;
            }
        }

        if(ok){
            return i;
        }
    }

}
ll discrete_root(ll y,ll m){/// solve x^y=m (mod mod)

    /// find primitive root
    ll proot=primitive_root(mod);

    /// solve discrete log
    ll pom=step(proot,y);
    ll invpom=step(pom,mod-2);
    ll nn=sqrt(mod);
    ll bigstep=step(pom,nn);

    ll right=m;
    ll left=1;

    map<ll,ll>mapa;
    mapa[right]=0;
    for(int i=1;i<nn;i++){
        right=(right*invpom)%mod;
        mapa[right]=i;
    }

    for(int i=0;i<=nn;i++){

        if(mapa.find(left)!=mapa.end())return step(proot,mapa[left]+i*nn);

        left=(left*bigstep)%mod;
    }

    return -1;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&k);
    for(int i=0;i<k;i++){
        scanf("%lld",&b[i]);
    }

    for(int i=0;i<k;i++){
        trans[i][k-1]=b[k-i-1];
        if(i<k-1)trans[i+1][i]=1;
        if(i==k-1)pwm[0][i]=1;
    }

    scanf("%d %lld",&n,&m);

    step_mat(trans,n-k);
    mmul(pwm,trans);

    ll pr=pwm[0][k-1];

    /// solve x^pr=m
    ll x=discrete_root(pr,m);
    cout<<x;

    return 0;
}
