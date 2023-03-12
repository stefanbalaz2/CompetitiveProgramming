/*

    idea:   its easy to see that the solution is number of
            i such that C(n-1,i)%m==0
            since m is ont prime, we can (due to Chineese remainder theorem)
            factorise it into p1^x1 * p2^x2 ...
            and solve for every p1^x1
            now the problem remains the same, we just have to solve for every pj^xj
            since even that isnt prime, we can calculate C with factorials and
            eliminate the pj factors from the denominator, we can always eliminate them
            all(easy to prove) and calculate the rest regularly

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int maxn=1e5+10;
struct md{
    ll base,mod,phi;
};
vector<md>vect;
pll fact[maxn],inv[maxn];
int n,rez[maxn];
ll m;
void factorise(ll x){

    for(ll i=2;i*i<=x;i++){
        if(x%i)continue;

        if(vect.size()==0)vect.pb({i,i,i-1});
        else if(vect.back().base==i)vect[vect.size()-1].mod*=i,vect[vect.size()-1].phi+=i-1;
        else vect.pb({i,i,i-1});

        x/=i;
        i--;
    }
    if(x>1){
        if(vect.size()==0)vect.pb({x,x,x-1});
        else if(vect.back().base==x)vect[vect.size()-1].mod*=x,vect[vect.size()-1].phi+=x-1;
        else vect.pb({x,x,x-1});
    }
}
ll step(ll base,ll pw,ll mod){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;
    }

    return ret;
}
ll c(int n,int k,ll mod,ll base){

    ll ret=fact[n].ff;
    ret=(ret*inv[k].ff)%mod;
    ret=(ret*inv[n-k].ff)%mod;

    ll pom=fact[n].ss-inv[k].ss-inv[n-k].ss;
    ret=(ret*step(base,pom,mod))%mod;

    return ret;
}
void solve(md x){

    fact[0]={1,0};
    inv[0]={1,0};

    for(int i=1;i<=n;i++){

        ll pom=i;
        ll pom2=0;

        while(pom%x.base==0){
            pom2++;
            pom/=x.base;
        }

        fact[i]={(fact[i-1].ff*pom)%x.mod,fact[i-1].ss+pom2};
        inv[i]={ step(fact[i].ff,x.phi-1,x.mod) , fact[i-1].ss+pom2 };
    }

    for(int i=0;i<n;i++)
        if(c(n-1,i,x.mod,x.base)==0)rez[i]++;

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    while(scanf("%d %lld",&n,&m)==2){

        if(n<=2){
            printf("0\n\n");
            continue;
        }

        vect.clear();
        for(int i=0;i<=n;i++)rez[i]=0;
        factorise(m);

        for(int i=0;i<vect.size();i++)
            solve(vect[i]);


        vector<int>v;
        for(int i=0;i<n;i++)
            if(rez[i]==vect.size())v.pb(i+1);

        printf("%d\n",v.size());
        for(int i=0;i<v.size();i++)
            if(i==v.size()-1)printf("%d",v[i]);
            else printf("%d ",v[i]);
        printf("\n");

    }

    return 0;
}
